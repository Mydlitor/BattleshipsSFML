#pragma once

#include "GameState.h"
#include "Ship.h"
#include "Button.h"

class ShipPlacementState :
    public State
{
private:
    // Variables
    sf::Vector2f playerGridStartPosition;
    int gridSize;
    float fieldSize;

    // Mouse
    sf::Vector2i mousePosGrid;

    // Ship placing
    Ship* selectedShip;
    int shipSizeInCells;
    bool isShipSelected;
    bool allShipsPlaced;

    // Text
    sf::Text titleText;
    sf::Text instructionMsg;
    sf::Text playerFleetText;
    std::vector<sf::Text> columnIndexes;
    std::vector<sf::Text> rowIndexes;

    // State objects
    std::vector<std::vector<Field*>> playerGrid;
    std::map<std::string, Ship*> ships;
    std::map<std::string, Button*> buttons;

    // Private functions
    void initVariables();
    void initText();
    void initGrid();
    void initShips();
    void initButtons();
    void initEnemyBoard();

public:
    ShipPlacementState(sf::RenderWindow* window, std::stack<State*>* states, int** playerBoard, int** enemyBoard);
    virtual ~ShipPlacementState();

    // Functions
    void endState();

    // Update
    void updateInput();
    void updateMousePosGrid(); // Stores the field indices if the cursor is over the board, or assigns -1 if the cursor is outside the board.
    void updateShips(); // Records the last clicked ship. Changes color if the cursor is over the object or clicked.
    void updateGrid(); // Updates the grid, displaying the set ships, and shows the position of the currently placing ship.
    void placeSelectedShip(); // Places a selected ship on the game board at the specified location.
    bool isValidPlacement(); // Checks whether it is allowed to place the ship in a specific location.
    bool checkIfAllShipsArePlaced(); // Returns true if all ships are placed, false otherwise. Enables the activation of the Start Button.
    void updateButtons(); // Enables progression to the next stage. Changes color if the cursor is over the button.
    void update();

    // Render
    void renderText(sf::RenderTarget& target);
    void renderGrid(sf::RenderTarget* target = nullptr);
    void renderShips(sf::RenderTarget* target = nullptr);
    void renderButtons(sf::RenderTarget* target = nullptr);
    void render(sf::RenderTarget* target = nullptr);
};

