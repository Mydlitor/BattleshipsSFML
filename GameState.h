#pragma once

#include "State.h"
#include "Field.h"
//#include "ResultBar.h"

class GameState :
    public State
{
private:
    // Variables
    sf::Vector2f playerGridStartPosition;
    sf::Vector2f enemyGridStartPosition;
    int gridSize;
    float fieldSize;
    bool result;

    // Mouse
    sf::Vector2i mousePosGrid;
   
    // Text
    std::vector<sf::Text> playerRowIndexes;
    std::vector<sf::Text> playerColumnIndexes;
    std::vector<sf::Text> enemyRowIndexes;
    std::vector<sf::Text> enemyColumnIndexes;
    sf::Text playerTitleText;
    sf::Text enemyTitleText;

    // Game objects
    std::vector<std::vector<Field*>> playerGrid;
    std::vector<std::vector<Field*>> enemyGrid;

    // Result bar
    //ResultBar resultBar;

    // Private functions
    void initVariables();
    void initText();
    void initGrids();

public:
    GameState(sf::RenderWindow* window, std::stack<State*>* states, int** playerBoard, int** enemyBoard);
    virtual ~GameState();

    // Functions
    void endState();

    // Update
    void updateInput();
    void updateMousePosGrid();
    void updateGrids();
    void update();

    // Render
    void renderText(sf::RenderTarget& target);
    void renderGrids(sf::RenderTarget* target = nullptr);
    void render(sf::RenderTarget* target = nullptr);
};

