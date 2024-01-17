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


public:
	ResultBar(sf::RenderWindow& window);
	~ResultBar();

	// Functions
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget& target);
};

