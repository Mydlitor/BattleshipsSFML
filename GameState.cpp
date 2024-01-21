#include "GameState.h"

// Initializer functions
void GameState::initVariables()
{
    this->fieldNames = { "Empty", "Ship", "Hit", "Sank", "Miss", "Blocked" };
    this->playerGridStartPosition = sf::Vector2f(450.f, 250.f);
    this->enemyGridStartPosition = sf::Vector2f(1000.f, 250.f);
    this->gridSize = 10;
    this->fieldSize = 40.f;
    this->player_move = true;
    this->A.x = -1;
    this->A.y = -1;
    this->prev_guess.x = -1;
    this->prev_guess.y = -1;
    this->dir = -1;
    this->ship_hit = false;
    this->result =0;
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
        for (int j = 0; j < this->gridSize; ++j)
        {
            // Initialize player' grid
            this->playerGrid[i][j] = new Field(i, j,
                this->playerGridStartPosition.x,
                this->playerGridStartPosition.y,
                this->fieldSize,
                false,
                sf::Color(37, 65, 99), sf::Color(255, 255, 255), sf::Color(8, 98, 201),
                sf::Color(220, 0, 0), sf::Color(230, 230, 230), sf::Color(230, 230, 230));

            this->enemyGrid[i][j] = new Field(i, j,
                this->enemyGridStartPosition.x,
                this->enemyGridStartPosition.y,
                this->fieldSize,
                true,
                sf::Color(37, 65, 99), sf::Color(255, 255, 255), sf::Color(8, 98, 201),
                sf::Color(220, 0, 0), sf::Color(230, 230, 230), sf::Color(230, 230, 230));
        }
    }
}

void GameState::initLegend()
{
    this->legendText = sf::Text("LEGEND", this->font1, 30);
    this->legendText.setFillColor(sf::Color(37, 65, 99));
    this->legendText.setPosition(this->playerGridStartPosition.x - 360.f, this->playerGridStartPosition.y);

    for (int i = 0; i < 6; ++i)
    {
        this->legendFieldsText[this->fieldNames[i]] = sf::Text(this->fieldNames[i], this->font2, 30);
        this->legendFieldsText[this->fieldNames[i]].setFillColor(sf::Color(37, 65, 99));
        this->legendFieldsText[this->fieldNames[i]].setPosition(this->playerGridStartPosition.x - 300.f, this->playerGridStartPosition.y + 50.f + i * 50);

        this->legendFields[this->fieldNames[i]] = new Field(0, 0,
            this->playerGridStartPosition.x - 360.f,
            this->playerGridStartPosition.y + 50.f + i * 50,
            this->fieldSize,
            false,
            sf::Color(37, 65, 99), sf::Color(255, 255, 255), sf::Color(8, 98, 201),
            sf::Color(220, 0, 0), sf::Color(230, 230, 230), sf::Color(230, 230, 230)
        );

        this->legendFields[this->fieldNames[i]]->update(i);
    }
}

void GameState::initResultBar()
{
    this->resultBar = new ResultBar(*this->window, &this->font1, this->result);

    this->backToMenuButton = new Button(
        1500.f,
        55.f,
        250, 70,
        30, &this->font1, "Back To Menu", 
        sf::Color(5, 62, 127), sf::Color(4, 50, 102), sf::Color(0, 0, 180), sf::Color::White);
}

// Constructors / Destructors
GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states, int** playerBoard, int** enemyBoard)
    : State(window, states, playerBoard, enemyBoard)
{
    this->initFonts();
    this->initAudio();
    this->initVariables();
    this->initText();
    this->initLegend();
    this->initGrids();
    this->initResultBar();
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

    auto field = this->legendFields.begin();
    for (field = this->legendFields.begin(); field != this->legendFields.end(); ++field)
    {
        delete field->second;
    }

    for (int i = 0; i < 10; ++i) {
        delete[] playerBoard[i];
        delete[] enemyBoard[i];
    }
    delete[] playerBoard;
    delete[] enemyBoard;

    delete this->resultBar;
    delete this->backToMenuButton;
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

Point GameState::updateMousePosGrid()
{
    Point A{ 0,0 };
    if (this->mousePosView.x >= this->enemyGridStartPosition.x && this->mousePosView.x <= this->enemyGridStartPosition.x + 400.f
        && this->mousePosView.y >= this->enemyGridStartPosition.y && this->mousePosView.y <= this->enemyGridStartPosition.y + 400.f)
    {
        this->mousePosGrid.y = static_cast<int>((this->mousePosView.x - this->enemyGridStartPosition.x) / this->fieldSize);
        this->mousePosGrid.x = static_cast<int>((this->mousePosView.y - this->enemyGridStartPosition.y) / this->fieldSize);
        A.x = mousePosGrid.x;
        A.y = mousePosGrid.y;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && (enemyBoard[A.x][A.y] == 0 || enemyBoard[A.x][A.y] == 1))
            return A;
        else
        {
            A.x = -1;
            A.y = -1;
            return A;
        }
    }
    else
    {
        A.x = -1;
        A.y = -1;
        return A;
    }
}

void GameState::updateGrids() //update grida //dobrze
{
    for (int i = 0; i < this->gridSize; ++i)
    {
        for (int j = 0; j < this->gridSize; ++j)
        {
            this->playerGrid[i][j]->update(this->playerBoard[i][j]);
            this->enemyGrid[i][j]->update(this->enemyBoard[i][j]);
            if(this->enemyBoard[i][j]!=0&& this->enemyBoard[i][j]!=1)
                this->enemyGrid[A.x][A.y]->reveal();
        }
    }
}

bool GameState::cordsOnBoard(Point A)
{
    if (A.x < 0 || A.x > 9 || A.y < 0 || A.y > 9)
        return false;
    return true;
}

void GameState::sAB(Point& A, Point& B)
{
    if (A.x > B.x) std::swap(A.x, B.x);
    if (A.y > B.y) std::swap(A.y, B.y);
}

int GameState::winCondition()
{
    int a=0,b = 0;
    //player win - 1
    //bot win - 2
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (enemyBoard[i][j] == 3)
                a++;
            if (playerBoard[i][j] == 3)
                b++;
        }
    }
    if (a == 17)
        return 1;
    else if (b == 17)
        return 2;
    else
        return 0;
}

bool GameState::checkSank(Point A, int player) //1-player  2-bot
{
    int val[] = { 0,1,0,-1,0 };
    Begin = A;
    End = A;
    if (player == 1)
    {
        for (int i = 0; i < 4; i++)
        {
            Point B = A;
            B.x += val[i];
            B.y += val[i + 1];
            if (!cordsOnBoard(B))
                continue;
            else
            {
                if (playerBoard[B.x][B.y] == 1)
                    return false;
                while (playerBoard[B.x][B.y] == 2)
                {
                    if (i < 2) Begin = B;
                    else End = B;
                    B.x += val[i];
                    B.y += val[i + 1];
                    if (!cordsOnBoard(B))
                        break;
                    if (playerBoard[B.x][B.y] == 1)
                        return false;
                }
            }
        }
        playerBoard[A.x][A.y] = 3;
    }
    else
    {
        for (int i = 0; i < 4; i++)
        {
            Point B = A;
            B.x += val[i];
            B.y += val[i + 1];
            if (!cordsOnBoard(B))
                continue;
            else
            {
                if (enemyBoard[B.x][B.y] == 1)
                    return false;
                while (enemyBoard[B.x][B.y] == 2)
                {
                    if (i < 2) Begin = B;
                    else End = B;
                    B.x += val[i];
                    B.y += val[i + 1];
                    if (!cordsOnBoard(B))
                        break;
                    if (enemyBoard[B.x][B.y] == 1)
                        return false;
                }
            }
        }
        enemyBoard[A.x][A.y] = 3;
    }
    return true;
}

void GameState::updateSank(int player)
{
    Point A = Begin;
    Point B = End;
    sAB(A, B);
    Point Ap{ A }, Bp{ B };
    if (A.x > 0) Ap.x--;
    if (A.y > 0) Ap.y--;
    if (B.x < 9) Bp.x++;
    if (B.y < 9) Bp.y++;
    if (player == 1)
    {
        for (int x = Ap.x; x <= Bp.x; x++)
        {
            for (int y = Ap.y; y <= Bp.y; y++)
            {
                playerBoard[x][y] = 6;
            }
        }
        for (int x = A.x; x <= B.x; x++)
        {
            for (int y = A.y; y <= B.y; y++)
            {
                playerBoard[x][y] = 3;
            }
        }
    }
    else
    {
        for (int x = Ap.x; x <= Bp.x; x++)
        {
            for (int y = Ap.y; y <= Bp.y; y++)
            {
                enemyBoard[x][y] = 5;
                this->enemyGrid[x][y]->reveal();
            }
        }
        for (int x = A.x; x <= B.x; x++)
        {
            for (int y = A.y; y <= B.y; y++)
            {
                enemyBoard[x][y] = 3;
            }
        }
    }
}



bool GameState::updatePlayerBoard(Point A)
{
    switch (playerBoard[A.x][A.y])
    {
    case 0:
        playerBoard[A.x][A.y] = 4;
        return false;
        break;
    case 1:
        playerBoard[A.x][A.y] = 2;
        ship_hit = true;
        if (checkSank(A, 1))
        {
            updateSank(1);
            ship_hit = false;
            dir = -1;
        }   
        return true;
        break;
    default:
        return false;
        break;
    }
}

bool GameState::updateBotBoard(Point A)
{
    switch (enemyBoard[A.x][A.y])
    {
    case 0:
        enemyBoard[A.x][A.y] = 4;
        return false;
        break;
    case 1:
        enemyBoard[A.x][A.y] = 2;
        if (checkSank(A, 2))
        {
            updateSank(2);
        }
        return true;
        break;
    default:
        return false;
        break;
    }
}

void GameState::updateButton()
{
    this->backToMenuButton->update(this->mousePosView);

    if (this->backToMenuButton->isPressed())
    {
        for (int i = 0; i < this->gridSize; i++)
        {
            for (int j = 0; j < this->gridSize; j++)
            {
                this->playerBoard[i][j] = 0;
                this->playerGrid[i][j]->update(0);
                this->enemyBoard[i][j] = 0;
                this->enemyGrid[i][j]->update(0);
            }
        }
        this->selectSound.play();
        this->states->push(new MainMenuState(this->window, this->states, this->playerBoard, this->enemyBoard));
    }
}

bool GameState::guessingRules(Point A, int b)
{
    if (!cordsOnBoard(A))
        return false;

    int val[] = { 0,1,0,-1,0 };

    if (b == 1) //1st guess
    {
        if (playerBoard[A.x][A.y] == 2 || playerBoard[A.x][A.y] == 3 || playerBoard[A.x][A.y] == 4 || playerBoard[A.x][A.y] == 6)
            return false;
    }

    else if (b == 2) //2nd and following guesses
    {
        if (playerBoard[A.x][A.y] == 6 || playerBoard[A.x][A.y] == 4)
            return false;
    }
    return true;
}

Point GameState::botGuess()
{
    Point A = prev_guess;
    int val[] = { 0,1,0,-1,0 };

    if (!ship_hit) //if bot didn't guess correctly before, or it is a first guess, or he sank the previous ship
    {
        do {
            A.x = rand() % 10;
            A.y = rand() % 10;
        } while (!guessingRules(A, 1));
        if (playerBoard[A.x][A.y] == 1) //if the oncoming guess is going to hit the ship
            prev_guess = A;
        return A;
    }

    else
    {
        if (dir!=-1)
        {
            while (playerBoard[A.x][A.y] == 2)
            {
                A.x += val[dir];
                A.y += val[dir + 1];
            }
            //teraz nie jest juz na 2
            if (guessingRules(A, 2))
            {
                return A;
            }

            A = prev_guess;
            while (playerBoard[A.x][A.y] == 2)
            {
                A.x -= val[dir];
                A.y -= val[dir + 1];
            }
            //teraz nie jest juz na 2
            if (guessingRules(A, 2))
            {
                return A;
            }
        }
        else
        {
            int z = 0;
            do { //strzelanie dopoki nie trafi drugiego kawalka statku
                A = prev_guess;
                z = rand() % 4;
                A.x += val[z];
                A.y += val[z + 1];
            } while (!guessingRules(A, 2));
            if (playerBoard[A.x][A.y] == 1)
                dir = z % 2; //0-y 1-x
            return A;
        }
    }
}



void GameState::update() //main game loop
{
    this->updateMousePositions();
    A = this->updateMousePosGrid();

    if (result == 0)
    {
        if (player_move)
        {
            //coords of mouse pos on grid
            if (A.x != -1)
            {
                //player move
                if (this->updateBotBoard(A))
                    player_move = true;
                else
                    player_move = false;
                this->enemyGrid[A.x][A.y]->reveal();
            }
        }
        else
        {
            //bot move
            B = this->botGuess();
            if (this->updatePlayerBoard(B))
                player_move = false;
            else
                player_move = true;
            sf::sleep(sf::milliseconds(750));
        }  
        this->updateGrids();

        this->result = checkWin();
    }

    this->updateInput();

    this->updateButton();
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

    // Legend text
    target.draw(this->legendText);

    for (auto& text : this->legendFieldsText)
    {
        target.draw(text.second);
    }
}

void GameState::renderLegend(sf::RenderTarget* target)
{
    for (auto& field : this->legendFields)
    {
        field.second->render(target);
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

void GameState::renderResultBar(sf::RenderTarget& target)
{
    this->resultBar->render(target);
    this->backToMenuButton->render(&target);
}

void GameState::render(sf::RenderTarget* target)
{
    this->window->clear(sf::Color(255, 255, 255));

    this->renderText(*this->window);

    this->renderLegend(target);

    this->renderGrids(target);

    if (this->result != 0)
    {
        this->resultBar->updateResult(this->result);
        this->renderResultBar(*this->window);
    }
        

    this->window->display();
}

void GameState::consoleDebug()
{
    std::cout << "Player move: " << player_move << "\nA: " << A.x << "," << A.y << "\n\n";
    sf::sleep(sf::milliseconds(1000));
}

int GameState::checkWin()
{
    int a = 0;
    //0- nobody won yet
    //1- player won
    //2- bot won
    for (int i = 0; i < 10; i++) //player
    {
        for (int j = 0; j < 10; j++)
        {
            if (enemyBoard[i][j] == 3)
                a++;
        }
    }
    if (a == 17) return 1;
    a = 0;
    for (int i = 0; i < 10; i++) //bot
    {
        for (int j = 0; j < 10; j++)
        {
            if (playerBoard[i][j] == 3)
                a++;
        }
    }
    if (a == 17) return 2;
    return 0;
}
