#include "State.h"

void State::initFonts()
{
	if (!this->font1.loadFromFile("assets\\fonts\\Codec Pro ExtraBold.ttf") || !this->font2.loadFromFile("assets\\fonts\\Codec Pro Light.ttf"))
	{
		std::cout << "ERROR::Menu::INITFONTS::Failed to load font!" << "\n";
	}
}

void State::initAudio()
{
	if (!this->selectSoundBuffer.loadFromFile("assets\\audio\\select.mp3") || 
		!this->placingSoundBuffer.loadFromFile("assets\\audio\\placing.mp3") ||
		!this->resetSoundBuffer.loadFromFile("assets\\audio\\reset.mp3") ||
		!this->errorSoundBuffer.loadFromFile("assets\\audio\\error_test.mp3") ||
		!this->hitSoundBuffer.loadFromFile("assets\\audio\\shot.mp3")
		)
	{
		std::cout << "ERROR::State::INITAUDIO::Failed to load audio!" << "\n";
	}

	this->selectSound.setBuffer(this->selectSoundBuffer);
	this->placingSound.setBuffer(this->placingSoundBuffer);
	this->resetSound.setBuffer(this->resetSoundBuffer);
	this->errorSound.setBuffer(this->errorSoundBuffer);
	this->hitSound.setBuffer(this->hitSoundBuffer);
}

State::State(sf::RenderWindow* window, std::stack<State*>* states, int** playerBoard, int** enemyBoard)
{
	this->window = window;
	this->states = states;
	this->playerBoard = playerBoard;
	this->enemyBoard = enemyBoard;
	this->quit = false;
}

State::~State()
{

}

const bool & State::getQuit() const
{
	return this->quit;
}

void State::checkForQuit()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		this->quit = true;
	}
}

void State::updateMousePositions()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}
