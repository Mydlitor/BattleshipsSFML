#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Menu
{
private:
	// Variables
	// Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	// Mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// Resources
	sf::Font font;

	// Text
	sf::Text titleText;

	// Menu objects
	enum MenuOptions {
		Start,
		Exit
	};

	// Private functions
	void initVariables();
	void initWindow();
	void initFonts();
	void initText();

public:
	// Constructors / Destructors
	Menu();
	virtual ~Menu();

	// Accessors
	const bool running() const;

	// Functions
	void pollEvents();
	void updateMousePositions();
	void update();

	void renderText(sf::RenderTarget& target);
	void render();
};
