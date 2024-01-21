#include "Game.h"

// Static functions

// Initializer functions
void Game::initWindow()
{
    //this->videoMode.height = 1080;
    //this->videoMode.width = 1920;
    this->videoMode = sf::VideoMode::getDesktopMode();
    //this->window = new sf::RenderWindow(this->videoMode, "Battleship Game", sf::Style::Close);
    this->window = new sf::RenderWindow(this->videoMode, "Battleship Game", sf::Style::Fullscreen);
    this->window->setFramerateLimit(165);
}

void Game::initBoards()
{
    this->playerBoard = new int* [10];
    this->enemyBoard = new int* [10];

    for (int i = 0; i < 10; ++i)
    {
        this->playerBoard[i] = new int[10];
        this->enemyBoard[i] = new int[10];
    }

    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; j++)
        {
            playerBoard[i][j] = 0;
            enemyBoard[i][j] = 0;
        }
    }
}

void Game::initStates()
{
    this->states.push(new MainMenuState(this->window, &this->states, this->playerBoard, this->enemyBoard));
}

// Constructors / Destructors
Game::Game()
{
    this->initWindow();
    this->initBoards();
    this->initStates();
}

Game::~Game()
{
    for (int i = 0; i < 10; ++i) {
        delete[] playerBoard[i];
        delete[] enemyBoard[i];
    }
    delete[] playerBoard;
    delete[] enemyBoard;

    delete this->window;

    while (!this->states.empty())
    {
        delete this->states.top();
        this->states.pop();
    }
}

// Functions
void Game::endApplication()
{
    std::cout << "Ending Application!" << "\n";
}

void Game::updateSFMLEvents()
{
    while (this->window->pollEvent(this->sfEvent))
    {
        if (this->sfEvent.type == sf::Event::Closed)
            this->window->close();
    }
}

void Game::update()
{
    this->updateSFMLEvents();

    if (!this->states.empty())
    {
        this->states.top()->update();

        if (this->states.top()->getQuit())
        {
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }
    }
    // Application end
    else
    {
        this->endApplication();
        this->window->close();
    }
}

void Game::render()
{
    this->window->clear();

    // Render items
    if (!this->states.empty())
        this->states.top()->render(this->window);

    this->window->display();
}

void Game::run()
{
    while (this->window->isOpen())
    {
        this->render();
        this->update();
        this->render();
    }
}
