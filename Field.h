#pragma once

#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>


class Field
{
private:
	bool hidden;
	bool checked;
	bool hovered;
	float crossLength;

	// Field shape
	sf::RectangleShape shape;

	// Cross shape
	sf::RectangleShape bar1;
	sf::RectangleShape bar2;

	// Dot shape
	sf::CircleShape dot;

	// Colors
	sf::Color borderColor;
	sf::Color emptyColor;
	sf::Color shipColor;
	sf::Color hitColor;
	sf::Color sankColor;
	sf::Color missColor;

public:
	Field(int x, int y, float offsetX, float offsetY, float size, bool status, sf::Color borderColor, sf::Color emptyColor, sf::Color shipColor, sf::Color hitColor, sf::Color sankColor, sf::Color missColor);
	~Field();
	
	// Functions
	void setCross(sf::Color, float);
	void setDot();
	void reveal();
	void setHovered(bool isHovered);

	// Accessors
	const bool isHidden() const;
	const bool isHovered() const;
	const sf::RectangleShape getShape() const;
	const bool isMouseOverShape(const sf::Vector2f mousePos) const;

	void update(short unsigned fieldState);
	void render(sf::RenderTarget* target);
};

