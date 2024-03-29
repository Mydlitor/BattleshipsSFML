#include "MainMenuState.h"

// Initializer functions
void MainMenuState::initVariables()
{

}

void MainMenuState::initBackground()
{
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);

	this->background.setFillColor(sf::Color(255, 255, 255));

	if (!this->iconTexture.loadFromFile("assets\\graphics\\icon.png"))
	{
		std::cout << "ERROR::MainMenuState::INITIMAGE::Failed to load icon!" << "\n";
	}

	this->iconSprite.setTexture(this->iconTexture);

	this->iconSprite.setPosition(
		this->window->getSize().x / 2.f - this->iconSprite.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 3.f - 250.f
	);
}

void MainMenuState::initText()
{
	this->titleText = sf::Text("Battleship Game", this->font1, 80);
	this->titleText.setFillColor(sf::Color(37, 65, 99));
	this->titleText.setPosition(
		this->window->getSize().x / 2.f - this->titleText.getGlobalBounds().width / 2.f, 
		this->window->getSize().y / 3.f);

	this->createdBy = sf::Text("Created by", this->font2, 30);
	this->createdBy.setFillColor(sf::Color(37, 65, 99));
	this->createdBy.setPosition(
		this->window->getSize().x / 2.f - this->createdBy.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 3.f + 350.f
	);

	this->authorsNames = sf::Text("Jakub Sputo & Kacper Strzesak", this->font2, 30);
	this->authorsNames.setFillColor(sf::Color(37, 65, 99));
	this->authorsNames.setPosition(
		this->window->getSize().x / 2.f - this->authorsNames.getGlobalBounds().width / 2.f, 
		this->window->getSize().y / 3.f + 390.f
	);
}

void MainMenuState::initButtons()
{
	this->buttons["GAME_STATE"] = new Button(
		this->window->getSize().x / 2.f - 250 / 2.f,
		this->window->getSize().y / 2.f - 70 / 2.f,
		250, 70,
		30, &this->font1, "Start Game",
		sf::Color(8, 98, 201), sf::Color(5, 78, 161), sf::Color(4, 58, 120), sf::Color(255, 255, 255));
	
	this->buttons["EXIT_STATE"] = new Button(
		this->window->getSize().x / 2.f - 250 / 2.f,
		this->window->getSize().y / 2.f + 100 / 2.f,
		250, 70,
		30, &this->font1, "Quit",
		sf::Color(8, 98, 201), sf::Color(5, 78, 161), sf::Color(4, 58, 120), sf::Color(255, 255, 255));
}

// Constructors / Destructors
MainMenuState::MainMenuState(sf::RenderWindow* window, std::stack<State*>* states, int** playerBoard, int** enemyBoard)
	: State(window, states, playerBoard, enemyBoard)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initAudio();
	this->initText();
	this->initButtons();
}

MainMenuState::~MainMenuState()
{
	delete this->window;

	auto button = this->buttons.begin();
	for (button = this->buttons.begin(); button != this->buttons.end(); ++button)
	{
		delete button->second;
	}
}

// Functions
void MainMenuState::endState()
{
	//std::cout << "Ending MainMenuState!" << "\n";
}

void MainMenuState::updateInput()
{
	this->checkForQuit();
}

void MainMenuState::updateButtons()
{
	/* Updates all the buttons in the state and handles their functionality */
	for (auto &button : this->buttons)
	{
		button.second->update(this->mousePosView);
	}

	// New game
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->selectSound.play();
		this->states->push(new ShipPlacementState(this->window, this->states, this->playerBoard, this->enemyBoard));
	}

	// Quit the game
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->selectSound.play();
		this->quit = true;
	}
}

void MainMenuState::update()
{
	this->updateMousePositions();
	this->updateInput();
	this->updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget* target)
{
	for (auto& button : this->buttons)
	{
		button.second->render(target);
	}
}

void MainMenuState::renderText(sf::RenderTarget& target)
{
	target.draw(this->titleText);
	target.draw(this->createdBy);
	target.draw(this->authorsNames);
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderText(*this->window);

	target->draw(this->iconSprite);

	this->renderButtons(target);
}