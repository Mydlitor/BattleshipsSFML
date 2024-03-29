#pragma once

#include "State.h"
#include "MainMenuState.h"
#include "Field.h"
#include "Button.h"
#include "ResultBar.h"

class GameState :
    public State
{
private:
    // Variables
    sf::Vector2f playerGridStartPosition;
    sf::Vector2f enemyGridStartPosition;
    int gridSize;
    float fieldSize;
    int result;

    // Mouse
    sf::Vector2i mousePosGrid;
   
    // Text
    std::vector<sf::Text> playerRowIndexes;
    std::vector<sf::Text> playerColumnIndexes;
    std::vector<sf::Text> enemyRowIndexes;
    std::vector<sf::Text> enemyColumnIndexes;
    sf::Text playerTitleText;
    sf::Text enemyTitleText;
    sf::Text legendText;

    // Game objects
    Field *playerGrid[10][10];
    Field *enemyGrid[10][10];
    //std::vector<std::vector<Field*>> playerGrid;
    //std::vector<std::vector<Field*>> enemyGrid;

    // Legend objects
    std::map<std::string, Field*> legendFields;
    std::vector<std::string> fieldNames;
    std::map<std::string, sf::Text> legendFieldsText;

    // Result bar
    ResultBar* resultBar;
    Button* backToMenuButton;

    // Private functions
    void initVariables();
    void initText();
    void initGrids();
    void initLegend();
    void initResultBar();

public:
    GameState(sf::RenderWindow* window, std::stack<State*>* states, int** playerBoard, int** enemyBoard);
    virtual ~GameState();

    // Functions
    void endState();

    // Update
    void updateInput();
    Point updateMousePosGrid();
    void updateGrids();
    void updateButton();
    void update();

    bool updatePlayerBoard(Point A);
    bool updateBotBoard(Point A);

    bool player_move = true;
    Point prev_guess;
    Point botGuess();
    Point A;
    Point B;
    Point Begin, End;
    int dir;
    bool ship_hit;
    int checkWin();
    bool checkSank(Point, int);
    void updateSank(int);
    bool cordsOnBoard(Point);
    bool guessingRules(Point, int);
    void sAB(Point& A, Point& B);
    int winCondition();

    // Render
    void renderText(sf::RenderTarget& target);
    void renderLegend(sf::RenderTarget* target);
    void renderGrids(sf::RenderTarget* target = nullptr);
    void renderResultBar(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = nullptr);

    void consoleDebug();
};
