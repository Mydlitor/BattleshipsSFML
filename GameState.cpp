#include "GameState.h"

// Initializer functions
void GameState::initVariables()
{
    this->playerGridStartPosition = sf::Vector2f(450.f, 250.f);
    this->enemyGridStartPosition = sf::Vector2f(1000.f, 250.f);
    this->gridSize = 10;
    this->fieldSize = 40.f;
}

void GameState::initText()
{
    // PLAYER TEXT
    // Set up player title text
    this->playerTitleText = sf::Text("YOU", this->font1, 30);
    this->playerTitleText.setFillColor(sf::Color(37, 65, 99));
    this->playerTitleText.setPosition(this->playerGridStartPosition.x, this->playerGridStartPosition.y - 80.f);

    // Initialize column indexes for player
    for (int i = 0; i < 10; ++i)
    {
        this->playerColumnIndexes.push_back(sf::Text(std::string(1, static_cast<char>('A' + i)), this->font1, 20));
        this->playerColumnIndexes[i].setFillColor(sf::Color(37, 65, 99));
        this->playerColumnIndexes[i].setPosition({ this->playerGridStartPosition.x + 15.f + i * this->fieldSize, this->playerGridStartPosition.y - 30.f });
    }

    // Initialize row indexes for player
    for (int i = 0; i < 10; ++i)
    {
        this->playerRowIndexes.push_back(sf::Text(std::to_string(i + 1), this->font1, 20));
        this->playerRowIndexes[i].setFillColor(sf::Color(37, 65, 99));
        this->playerRowIndexes[i].setPosition({ this->playerGridStartPosition.x - 30.f, this->playerGridStartPosition.y + 5.f + i * this->fieldSize });
    }

    // ENEMY TEXT
    // Set up enemy title text
    this->enemyTitleText = sf::Text("ENEMY", this->font1, 30);
    this->enemyTitleText.setFillColor(sf::Color(37, 65, 99));
    this->enemyTitleText.setPosition(this->enemyGridStartPosition.x, this->enemyGridStartPosition.y - 80.f);

    // Initialize column indexes for enemy
    for (int i = 0; i < 10; ++i)
    {
        this->enemyColumnIndexes.push_back(sf::Text(std::string(1, static_cast<char>('A' + i)), this->font1, 20));
        this->enemyColumnIndexes[i].setFillColor(sf::Color(37, 65, 99));
        this->enemyColumnIndexes[i].setPosition({ this->enemyGridStartPosition.x + 15.f + i * this->fieldSize, this->enemyGridStartPosition.y - 30.f });
    }

    //// Initialize row indexes for enemy
    for (int i = 0; i < 10; ++i)
    {
        this->enemyRowIndexes.push_back(sf::Text(std::to_string(i + 1), this->font1, 20));
        this->enemyRowIndexes[i].setFillColor(sf::Color(37, 65, 99));
        this->enemyRowIndexes[i].setPosition({ this->enemyGridStartPosition.x - 30.f, this->enemyGridStartPosition.y + 5.f + i * this->fieldSize });
    }
}

void GameState::initGrids() {
    for (int i = 0; i < this->gridSize; ++i)
    {
        std::vector<Field*> p_row;
        std::vector<Field*> e_row;

        for (int j = 0; j < this->gridSize; ++j)
        {
            // Initialize player' grid
            p_row.push_back(new Field(
                i, j,
                this->playerGridStartPosition.x,
                this->playerGridStartPosition.y,
                this->fieldSize,
                false,
                sf::Color(37, 65, 99), sf::Color(255, 255, 255), sf::Color(8, 98, 201), 
                sf::Color(220, 0, 0), sf::Color(230, 230, 230), sf::Color(230, 230, 230)
            ));

            // Initialize enemy's grid
            e_row.push_back(new Field(
                i, j,
                this->enemyGridStartPosition.x,
                this->enemyGridStartPosition.y,
                this->fieldSize,
                true,
                sf::Color(37, 65, 99), sf::Color(255, 255, 255), sf::Color(8, 98, 201), 
                sf::Color(220, 0, 0), sf::Color(230, 230, 230), sf::Color(230, 230, 230)
            ));
        }

        this->playerGrid.push_back(p_row);
        this->enemyGrid.push_back(e_row);
    }
}

// Constructors / Destructors
GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states, int** playerBoard, int** enemyBoard)
    : State(window, states, playerBoard, enemyBoard)/*, resultBar(*window)*/
{
    this->initFonts();
    this->initAudio();
    this->initVariables();
    this->initText();
    this->initGrids();
}

GameState::~GameState()
{
    delete this->window;

    for (auto& row : this->playerGrid) {
        for (auto& field : row) {
            delete field;
        }
    }

    for (auto& row : this->enemyGrid) {
        for (auto& field : row) {
            delete field;
        }
    }
}

// Functions
void GameState::endState()
{
    std::cout << "Ending GameState!" << "\n";
}

void GameState::updateInput()
{
    this->checkForQuit();
}

void GameState::updateMousePosGrid()
{
    if (this->mousePosView.x >= this->enemyGridStartPosition.x && this->mousePosView.x <= this->enemyGridStartPosition.x + 400.f
        && this->mousePosView.y >= this->enemyGridStartPosition.y && this->mousePosView.y <= this->enemyGridStartPosition.y + 400.f)
    {
        this->mousePosGrid.y = static_cast<int>((this->mousePosView.x - this->enemyGridStartPosition.x) / this->fieldSize);
        this->mousePosGrid.x = static_cast<int>((this->mousePosView.y - this->enemyGridStartPosition.y) / this->fieldSize);
    }
    else
    {
        this->mousePosGrid.y = -1;
        this->mousePosGrid.x = -1;
    }
}

void GameState::updateGrids()
{
    for (int i = 0; i < this->gridSize; ++i)
    {
        for (int j = 0; j < this->gridSize; ++j)
        {
            this->playerGrid[i][j]->update(this->playerBoard[i][j]);
            this->enemyGrid[i][j]->update(this->enemyBoard[i][j]);

            if (this->enemyGrid[i][j]->isHidden() && sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->enemyGrid[i][j]->isMouseOverShape(mousePosView))
            {
                if (this->enemyBoard[i][j] == 0) this->enemyBoard[i][j] = 4;
                else if (this->enemyBoard[i][j] == 1)
                {
                    this->enemyBoard[i][j] = 2;
                    this->hitSound.play();
                }

                this->enemyGrid[i][j]->reveal();
                this->enemyGrid[i][j]->update(this->enemyBoard[i][j]);
            }
        }
    }
}

void GameState::update()
{
    this->updateMousePositions();
    this->updateMousePosGrid();
    this->updateInput();
    this->updateGrids();
}

void GameState::renderText(sf::RenderTarget& target)
{
    target.draw(this->playerTitleText);

    // Draw column indexes for player
    for (auto& index : this->playerColumnIndexes)
    {
        target.draw(index);
    }

    //// Draw row indexes for player
    for (auto& index : this->playerRowIndexes)
    {
        target.draw(index);
    }

    // Draw enemy text
    target.draw(this->enemyTitleText);

    //// Draw column indexes for enemy
    for (auto& index : this->enemyColumnIndexes)
    {
        target.draw(index);
    }

    //// Draw row indexes for enemy
    for (auto& index : this->enemyRowIndexes)
    {
        target.draw(index);
    }
}

void GameState::renderGrids(sf::RenderTarget* target)
{
    // Render player's grid
    for (auto& row : this->playerGrid) 
    {
        for (auto& field : row) 
        {
            field->render(target);
        }
    }

    // Render enemy's grid
    for (auto& row : this->enemyGrid)
    {
        for (auto& field : row)
        {
            field->render(target);
        }
    }
}

void GameState::render(sf::RenderTarget* target)
{
    this->window->clear(sf::Color(255, 255, 255));

    this->renderText(*this->window);

    this->renderGrids(target);

    this->window->display();
}
