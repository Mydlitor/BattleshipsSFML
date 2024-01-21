#pragma once

//#include "GameState.h"
#include "ShipPlacementState.h"
#include "Button.h"

class MainMenuState :
    public State
{
private:
    // Variables
    sf::RectangleShape background;
    sf::Texture iconTexture;
    sf::Sprite iconSprite;

    // Text
    sf::Text titleText;
    sf::Text authorsNames;

    // Menu buttons
    std::map<std::string, Button*> buttons;

    // Functions
    //void initKeybind();
    void initVariables();
    void initBackground();
    void initText();
    void initButtons();

public:
    MainMenuState(sf::RenderWindow* window, std::stack<State*>* states, int** playerBoard, int** enemyBoard);
    virtual ~MainMenuState();

    // Functions
    void endState();

    // Update
    void updateInput();
    void updateButtons();
    void update();

    // Render
    void renderButtons(sf::RenderTarget* target = nullptr);
    void renderText(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = nullptr);
};

