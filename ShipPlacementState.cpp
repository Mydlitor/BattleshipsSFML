#include "ShipPlacementState.h"

// Initializer functions
void ShipPlacementState::initVariables()
{
    this->playerGridStartPosition = sf::Vector2f(550.f, 250.f);
    this->gridSize = 10;
    this->fieldSize = 40.f;
}

void ShipPlacementState::initText() {
    // Initialize title
    this->titleText = sf::Text("Place your ships", this->font1, 52);
    this->titleText.setFillColor(sf::Color(37, 65, 99));
    this->titleText.setPosition(this->playerGridStartPosition.x, this->playerGridStartPosition.y - 150.f);

    // Initialize message for player
    this->instructionMsg = sf::Text("Rules:\n1) You need to place all your ships to start the game.\n2) Each ship must be positioned either vertically or horizontally.\n3) You can rotate ship by pressing 'RMB'.\n4) Ships can't be placed next to each other.", font2, 30);
    this->instructionMsg.setFillColor(sf::Color(37, 65, 99));
    this->instructionMsg.setPosition(this->playerGridStartPosition.x, this->playerGridStartPosition.y + 460.f);

    // Initialize playerFleetTexe
    this->playerFleetText = sf::Text("Your fleet:", this->font1, 30);
    this->playerFleetText.setFillColor(sf::Color(37, 65, 99));
    this->playerFleetText.setPosition(this->playerGridStartPosition.x + 500.f, this->playerGridStartPosition.y);

    // Initialize column indexes for player
    for (int i = 0; i < this->gridSize; ++i)
    {
        this->columnIndexes.push_back(sf::Text(std::string(1, static_cast<char>('A' + i)), this->font1, 20));
        this->columnIndexes[i].setFillColor(sf::Color(37, 65, 99));
        this->columnIndexes[i].setPosition({ this->playerGridStartPosition.x + 15.f + i * this->fieldSize, this->playerGridStartPosition.y - 30.f });
    }

    // Initialize row indexes for player
    for (int i = 0; i < this->gridSize; ++i)
    {
        this->rowIndexes.push_back(sf::Text(std::to_string(i + 1), this->font1, 20));
        this->rowIndexes[i].setFillColor(sf::Color(37, 65, 99));
        this->rowIndexes[i].setPosition({ this->playerGridStartPosition.x - 30.f, this->playerGridStartPosition.y + 5.f + i * this->fieldSize });
    }
}

void ShipPlacementState::initGrid() 
{
    // Initialize player's grid
    for (int i = 0; i < this->gridSize; ++i)
    {
        std::vector<Field*> p_row;

        for (int j = 0; j < this->gridSize; ++j)
        {
            p_row.push_back(new Field(
                i, j,
                this->playerGridStartPosition.x,
                this->playerGridStartPosition.y,
                this->fieldSize,
                false,
                sf::Color(37, 65, 99), sf::Color(255, 255, 255), sf::Color(8, 98, 201), sf::Color(8, 98, 201), sf::Color(8, 98, 201), sf::Color(8, 98, 201)
            ));
        }

        this->playerGrid.push_back(p_row);
    }
}

void ShipPlacementState::initShips()
{
    this->ships["CARRIER"] = new Ship(
        this->playerGridStartPosition.x + 500.f,
        this->playerGridStartPosition.y + 50.f,
        5 * this->fieldSize, this->fieldSize,
        sf::Color(8, 98, 201), sf::Color(5, 78, 161), sf::Color(4, 58, 120), sf::Color(220, 220, 220)
    );

    this->ships["BATTLESHIP"] = new Ship(
        this->playerGridStartPosition.x + 500.f,
        this->playerGridStartPosition.y + 110.f,
        4 * this->fieldSize, this->fieldSize,
        sf::Color(8, 98, 201), sf::Color(5, 78, 161), sf::Color(4, 58, 120), sf::Color(220, 220, 220)
    );

    this->ships["CRUISER"] = new Ship(
        this->playerGridStartPosition.x + 500.f,
        this->playerGridStartPosition.y + 170.f,
        3 * 41, 41,
        sf::Color(8, 98, 201), sf::Color(5, 78, 161), sf::Color(4, 58, 120), sf::Color(220, 220, 220)
    );

    this->ships["SUBMARINE"] = new Ship(
        this->playerGridStartPosition.x + 500.f,
        this->playerGridStartPosition.y + 230.f,
        3 * this->fieldSize, this->fieldSize,
        sf::Color(8, 98, 201), sf::Color(5, 78, 161), sf::Color(4, 58, 120), sf::Color(220, 220, 220)
    );

    this->ships["DESTROYER"] = new Ship(
        this->playerGridStartPosition.x + 500.f,
        this->playerGridStartPosition.y + 290.f,
        2 * this->fieldSize, this->fieldSize,
        sf::Color(8, 98, 201), sf::Color(5, 78, 161), sf::Color(4, 58, 120), sf::Color(220, 220, 220)
    );
}

void ShipPlacementState::initButtons()
{
    this->buttons["START"] = new Button(
        this->playerGridStartPosition.x + 500.f,
        this->playerGridStartPosition.y - 150.f,
        250, 70,
        30, &this->font1, "Start Game",
        sf::Color(8, 98, 201), sf::Color(5, 78, 161), sf::Color(4, 58, 120));

    this->buttons["RESET"] = new Button(
        this->playerGridStartPosition.x + 281.f,
        this->playerGridStartPosition.y + 420.f,
        120, 40,
        20, &this->font1, "Reset",
        sf::Color(8, 98, 201), sf::Color(5, 78, 161), sf::Color(4, 58, 120));
}

void ShipPlacementState::initEnemyBoard()
{
    enemyBoard[0][1] = 1;
    enemyBoard[0][2] = 1;
    enemyBoard[0][3] = 1;
    enemyBoard[0][4] = 1;

    enemyBoard[5][9] = 1;
    enemyBoard[6][9] = 1;
    enemyBoard[7][9] = 1;
    enemyBoard[8][9] = 1;
    enemyBoard[9][9] = 1;

    enemyBoard[2][4] = 1;
    enemyBoard[3][4] = 1;
    enemyBoard[4][4] = 1;

    enemyBoard[0][6] = 1;
    enemyBoard[0][7] = 1;
    enemyBoard[0][8] = 1;

    enemyBoard[6][6] = 1;
    enemyBoard[6][7] = 1;
}

// Constructors / Destructors
ShipPlacementState::ShipPlacementState(sf::RenderWindow* window, std::stack<State*>* states, int** playerBoard, int** enemyBoard)
	: State(window, states, playerBoard, enemyBoard)
{
	this->initFonts();
    this->initVariables();
    this->initGrid();
	this->initText();
    this->initAudio();
    this->initShips();
    this->initButtons();
    this->initEnemyBoard();
}

ShipPlacementState::~ShipPlacementState()
{
    delete this->window;

    auto ship = this->ships.begin();
    for (ship = this->ships.begin(); ship != this->ships.end(); ++ship)
    {
        delete ship->second;
    }

    delete this->selectedShip;

    delete this->buttons["START"];
    delete this->buttons["RESET"];
}

// Functions
void ShipPlacementState::endState()
{
	std::cout << "Ending GameState!" << "\n";
}

void ShipPlacementState::updateInput()
{
    this->checkForQuit();
}

void ShipPlacementState::updateMousePosGrid()
{
    if (this->mousePosView.x >= this->playerGridStartPosition.x && this->mousePosView.x <= this->playerGridStartPosition.x + 400.f
        && this->mousePosView.y >= this->playerGridStartPosition.y && this->mousePosView.y <= this->playerGridStartPosition.y + 400.f)
    {
        this->mousePosGrid.y = static_cast<int>((this->mousePosView.x - this->playerGridStartPosition.x) / this->fieldSize);
        this->mousePosGrid.x = static_cast<int>((this->mousePosView.y - this->playerGridStartPosition.y) / this->fieldSize);
    }
    else
    {
        this->mousePosGrid.y = -1;
        this->mousePosGrid.x = -1;
    }
}

void ShipPlacementState::updateShips()
{
    for (auto& ship : this->ships)
    {
        ship.second->update(this->mousePosView);

        // Check for ship selection
        if (ship.second->isPressed())
        {
            // Set ship as selected
            this->selectedShip = ship.second;
            this->isShipSelected = true;
            break;
        }
    }
}

void ShipPlacementState::placeSelectedShip()
{
    if (this->isShipSelected && this->selectedShip != nullptr && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        this->shipSizeInCells = static_cast<int>(this->selectedShip->getShape().getSize().x / this->fieldSize);

        if (isValidPlacement())
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
                // Set the ship in a vertical position
                for (int i = 0; i < this->shipSizeInCells; ++i)
                {
                    this->playerBoard[this->mousePosGrid.x + i][this->mousePosGrid.y] = 1;
                }
                this->placingSound.play();
            }
            else
            {
                // Set the ship in a horizontal position
                for (int i = 0; i < this->shipSizeInCells; ++i)
                {
                    this->playerBoard[this->mousePosGrid.x][this->mousePosGrid.y + i] = 1;
                }
                this->placingSound.play();
            }

            this->selectedShip->setPlaced(SHIP_PLACED);
            this->selectedShip = nullptr;
            this->isShipSelected = false;
        }
    }
}
// Do poprawienia
bool ShipPlacementState::isValidPlacement()
{
    if (this->mousePosGrid.y < 0 || this->mousePosGrid.y + this->shipSizeInCells > this->gridSize ||
        this->mousePosGrid.x < 0 || this->mousePosGrid.x + this->shipSizeInCells > this->gridSize)
    {
        return false; // Out of bounds
    }

    // Check for collisions and adjacency
    for (int i = -1; i <= this->shipSizeInCells; ++i)
    {
        for (int j = -1; j <= 1; ++j)
        {
            int checkRow = this->mousePosGrid.x + i;
            int checkColumn = this->mousePosGrid.y + j;

            if (checkRow >= 0 && checkRow < this->gridSize && checkColumn >= 0 && checkColumn < this->gridSize)
            {
                if (this->playerBoard[checkRow][checkColumn] != 0)
                {
                    return false; // Collision detected
                }
            }
        }
    }

    // Check for adjacency of ships in the same row or column
    for (int i = -1; i <= this->shipSizeInCells; ++i)
    {
        int checkRow = this->mousePosGrid.x + i;
        int checkColumn = this->mousePosGrid.y - 1;

        if (checkRow >= 0 && checkRow < this->gridSize && checkColumn >= 0 && checkColumn < this->gridSize &&
            this->playerBoard[checkRow][checkColumn] != 0)
        {
            return false; // Adjacency detected to the left
        }

        checkColumn = this->mousePosGrid.y + this->shipSizeInCells;

        if (checkRow >= 0 && checkRow < this->gridSize && checkColumn >= 0 && checkColumn < this->gridSize &&
            this->playerBoard[checkRow][checkColumn] != 0)
        {
            return false; // Adjacency detected to the right
        }
    }

    // Check for adjacency of ships in the same column
    for (int j = -1; j <= 1; ++j)
    {
        int checkRow = this->mousePosGrid.x - 1;
        int checkColumn = this->mousePosGrid.y + j;

        if (checkRow >= 0 && checkRow < this->gridSize && checkColumn >= 0 && checkColumn < this->gridSize &&
            this->playerBoard[checkRow][checkColumn] != 0)
        {
            return false; // Adjacency detected above
        }

        checkRow = this->mousePosGrid.x + this->shipSizeInCells;

        if (checkRow >= 0 && checkRow < this->gridSize && checkColumn >= 0 && checkColumn < this->gridSize &&
            this->playerBoard[checkRow][checkColumn] != 0)
        {
            return false; // Adjacency detected below
        }
    }

    return true; // Valid placement
}

void ShipPlacementState::updateGrid()
{
    for (int i = 0; i < this->gridSize; ++i)
    {
        for (int j = 0; j < this->gridSize; ++j)
        {
            this->playerGrid[i][j]->update(this->playerBoard[i][j]);
        }
    }

    if (this->isShipSelected && this->mousePosGrid.x != -1 && this->mousePosGrid.y != -1)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            for (int i = 0; i < this->shipSizeInCells; ++i)
            {
                if (this->mousePosGrid.x + i < this->gridSize && this->mousePosGrid.y < this->gridSize)
                    this->playerGrid[this->mousePosGrid.x + i][this->mousePosGrid.y]->update(1);
            }
        }
        else
        {
            for (int i = 0; i < this->shipSizeInCells; ++i)
            {
                if (this->mousePosGrid.x < this->gridSize && this->mousePosGrid.y + i < this->gridSize)
                    this->playerGrid[this->mousePosGrid.x][this->mousePosGrid.y + i]->update(1);
            }
        }
    }
}

bool ShipPlacementState::checkIfAllShipsArePlaced()
{
    for (const auto& ship : ships)
    {
        if (!ship.second->isPlaced())
        {
            return false; // If at least one ship is not placed yet, return false
        }
    }

    return true; // If all ships are placed, return true
}

void ShipPlacementState::updateButtons()
{
    this->buttons["START"]->update(this->mousePosView);
    this->buttons["RESET"]->update(this->mousePosView);

    this->allShipsPlaced = checkIfAllShipsArePlaced();

    if (this->buttons["START"]->isPressed())
    {
        this->selectSound.play();

        if (this->allShipsPlaced)
            this->states->push(new GameState(this->window, this->states, this->playerBoard, this->enemyBoard));
    }

    if (this->buttons["RESET"]->isPressed())
    {
        this->resetSound.play();

        for (int i = 0; i < this->gridSize; i++)
        {
            for (int j = 0; j < this->gridSize; j++)
            {
                this->playerBoard[i][j] = 0;
            }
        }

        for (auto& ship : this->ships)
        {
            ship.second->setPlaced(SHIP_IDLE);
            this->selectedShip = nullptr;
            this->isShipSelected = false;
        }
    }
}

void ShipPlacementState::update()
{
    this->updateInput();
    this->updateMousePositions();
    this->updateMousePosGrid();
    this->updateShips();
    this->placeSelectedShip();
    this->updateGrid();
    this->updateButtons();
}

void ShipPlacementState::renderText(sf::RenderTarget& target)
{
    // Render title
    target.draw(this->titleText);

    // Render message for player
	target.draw(this->instructionMsg);

    // "Your fleet" text
    target.draw(this->playerFleetText);

    // Draw column and row indexes for player
    for (auto& index : columnIndexes) 
    {
        target.draw(index);
    }
    for (auto& index : rowIndexes) 
    {
        target.draw(index);
    }
}

void ShipPlacementState::renderGrid(sf::RenderTarget* target) {
    // Draw player's grid
    for (auto& row : this->playerGrid)
    {
        for (auto& field : row)
        {
            field->render(target);
        }
    }
}

void ShipPlacementState::renderShips(sf::RenderTarget* target)
{
    // Draw ships next to the grid
    for (auto& ship : this->ships)
    {
        ship.second->render(target);
    }
}

void ShipPlacementState::renderButtons(sf::RenderTarget* target)
{
    this->buttons["START"]->render(target);
    this->buttons["RESET"]->render(target);
}

void ShipPlacementState::render(sf::RenderTarget* target)
{
    this->window->clear(sf::Color(255, 255, 255));

    this->renderText(*this->window);

    this->renderGrid(target);

    this->renderShips(target);

    this->renderButtons(target);

    this->window->display();
}