#include "Menu.h"
#include <iostream>

// Private functions
void Menu::initVariables()
{
    this->window = nullptr;

    // Menu logic
}

void Menu::initWindow()
{
    //this->videoMode.height = 1080;
    //this->videoMode.width = 1920;
    this->videoMode = sf::VideoMode::getDesktopMode();
    this->window = new sf::RenderWindow(this->videoMode, "Battleship Menu", sf::Style::Default);
    this->window->setFramerateLimit(60);
}

void Menu::initFonts()
{
    if (!this->font.loadFromFile("assets\\fonts\\Codec Pro ExtraBold.ttf"))
    {
        std::cout << "ERROR::Menu::INITFONTS::Failed to load font!" << "\n";
    }
}

void Menu::initText()
{
    // PLAYER TEXT
    // Set up player title text
    this->titleText = sf::Text("YOU", this->font, 30);
    this->titleText.setFillColor(sf::Color(37, 65, 99));
    this->titleText.setPosition(200.f, 200.f);
}

// Constructors / Destructors
Menu::Menu()
{
    this->initVariables();
    this->initWindow();
    this->initFonts();
    this->initText();
}

Menu::~Menu()
{
    delete this->window;
}

// Accessors
const bool Menu::running() const
{
    return this->window->isOpen();
}

// Functions
void Menu::pollEvents()
{
    // Event polling
    while (this->window->pollEvent(this->ev))
    {
        switch (this->ev.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->ev.key.code == sf::Keyboard::Escape)
                this->window->close();
            break;
        }
    }
}

void Menu::updateMousePositions()
{
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Menu::update()
{
    this->pollEvents();

    this->updateMousePositions();
}

void Menu::renderText(sf::RenderTarget& target)
{
    // Draw title text
    target.draw(this->titleText);
}

void Menu::render()
{
    /*
        Renders the menu objects.
    */

    this->window->clear(sf::Color(255, 255, 255));


    this->renderText(*this->window);

    this->window->display();
}
