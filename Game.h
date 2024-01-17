#pragma once

#include "MainMenuState.h"

class Game
{
private:
	// Variables
	sf::RenderWindow *window;
	sf::VideoMode videoMode;
	sf::Event sfEvent;

	// Boards
	int** playerBoard;
	int** enemyBoard;

	// States
	std::stack<State*> states;

	// Mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// Initialization
	void initWindow();
	void initStates();
	void initBoards();

public:
	// Constructors / Destructors
	Game();
	virtual ~Game();

	// Functions

	// Regular
	void endApplication();

	void updateSFMLEvents();

	// Update
	void update();

	// Render
	void render();
	void run();
};
