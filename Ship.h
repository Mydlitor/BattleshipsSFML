#pragma once

#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

enum ship_states { SHIP_IDLE = 0, SHIP_HOVER, SHIP_ACTIVE, SHIP_PLACED };

class Ship
{
private:
	short unsigned shipState;

	sf::RectangleShape shape;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;
	sf::Color placedColor;

public:
	Ship(float x, float y, float width, float height, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, sf::Color placedColor);
	~Ship();

	// Accessors
	const bool isPressed() const;
	const bool isPlaced() const;
	sf::RectangleShape getShape();
	void setPlaced(short unsigned state);

	// Functions
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);
};