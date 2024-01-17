#pragma once

#include <iostream>
#include <vector>
#include <stack>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class State
{
private:

protected:
	// Variables
	sf::RenderWindow* window;
	std::stack<State*>* states;
	int** playerBoard;
	int** enemyBoard;
	bool quit;

	// Mouse
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// Resources
	// Fonts
	sf::Font font1;
	sf::Font font2;
	// Audio
	sf::SoundBuffer selectSoundBuffer;
	sf::SoundBuffer placingSoundBuffer;
	sf::SoundBuffer resetSoundBuffer;
	sf::SoundBuffer errorSoundBuffer;
	sf::SoundBuffer hitSoundBuffer;

	sf::Sound selectSound;
	sf::Sound placingSound;
	sf::Sound resetSound;
	sf::Sound errorSound;
	sf::Sound hitSound;

	// Functions
	//virtual void updateInput() = 0;
	virtual void initFonts();
	virtual void initAudio();

public:
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

