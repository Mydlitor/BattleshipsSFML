#pragma once

#include <iostream>
#include <vector>
#include <stack>
#include <map>
//#include <windows.h>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

struct Point
{
	int x, y;
};

class State
{
private:

protected:
	// Variables
	sf::RenderWindow* window;
	std::stack<State*>* states;
	bool quit;

	// Mouse
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// Resources

	// - Fonts
	sf::Font font1;
	sf::Font font2;

	// - Audio
	sf::SoundBuffer selectSoundBuffer;
	sf::SoundBuffer placingSoundBuffer;
	sf::SoundBuffer resetSoundBuffer;
	sf::SoundBuffer missSoundBuffer;
	sf::SoundBuffer hitSoundBuffer;
	sf::SoundBuffer sinkSoundBuffer;

	sf::Sound selectSound;
	sf::Sound placingSound;
	sf::Sound resetSound;
	sf::Sound missSound;
	sf::Sound hitSound;
	sf::Sound sinkSound;

	// Functions
	virtual void initFonts();
	virtual void initAudio();

public:
	int** playerBoard;
	int** enemyBoard;

	//friend ShipPlacementState;

	State(sf::RenderWindow* window, std::stack<State*>* states, int** playerBoard, int** enemyBoard);
	virtual ~State();

	const bool& getQuit() const;

	virtual void checkForQuit();

	virtual void endState() = 0;
	virtual void updateMousePositions();
	virtual void updateInput() = 0;
	virtual void update() = 0;

	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

