#pragma once

#include <iostream>
#include <vector>

#include "Button.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

class ResultBar
{
private:
	sf::RectangleShape background;
	sf::RectangleShape container;
	sf::Text text;
	sf::Font* font;
	sf::String textContent;

public:
	ResultBar(sf::RenderWindow& window, sf::Font* font, int winner);
	~ResultBar();

	// Functions
	void updateResult(int winner);
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget& target);
};

