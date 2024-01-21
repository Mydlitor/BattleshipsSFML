#include "Field.h"

Field::Field(int x, int y, float offsetX, float offsetY, float size, bool status,
	sf::Color borderColor, sf::Color emptyColor, sf::Color shipColor, sf::Color hitColor, sf::Color sankColor, sf::Color missColor)
{
	this->hidden = status;
	this->crossLength = size;
	this->x = x;
	this->y = y;
	this->offsetX = offsetX;
	this->offsetY = offsetY;

	// Shape
	this->shape.setPosition(sf::Vector2f(y * size + offsetX, x * size + offsetY));
	this->shape.setSize(sf::Vector2f(size, size));

	// Colors
	this->borderColor = borderColor;
	this->emptyColor = emptyColor;
	this->shipColor = shipColor;
	this->hitColor = hitColor;
	this->sankColor = sankColor;
	this->missColor = missColor;

	// Shape border
	this->shape.setOutlineColor(this->borderColor);
	this->shape.setOutlineThickness(1.f);
}

Field::~Field()
{

}

// Update
void Field::update(short unsigned fieldState)
{
	if (!this->hidden)
		switch (fieldState)
		{
		case 0: // EMPTY
			this->shape.setFillColor(this->emptyColor);
			removeCross();
			break;

		case 1: // SHIP
			this->shape.setFillColor(this->shipColor);
			removeCross();
			break;

		case 2: // HIT
			this->shape.setFillColor(this->shipColor);
			setCross(sf::Color::Red, 4.5);
			break;

		case 3: // SANK
			this->shape.setFillColor(this->sankColor);
			setCross(sf::Color::Red, 4.5);
			break;

		case 4: // MISS
			this->shape.setFillColor(this->missColor);
			setDot();
			break;

		case 5: // BLOCKED
			this->shape.setFillColor(this->emptyColor);
			removeDot();
			setCross(sf::Color(60, 60, 60), 3.f);
			break;

		default:
			this->shape.setFillColor(this->emptyColor);
			break;
		}
}

void Field::setCross(sf::Color color, float size)
{
	// Cross
	this->bar1.setPosition(sf::Vector2f(
		this->y * this->crossLength + this->offsetX + 8.f,
		this->x * this->crossLength + this->offsetY + 5.f)
	);
	this->bar1.setSize(sf::Vector2f(this->crossLength - 2, size));
	this->bar1.setFillColor(color);
	this->bar1.setRotation(45);

	this->bar2.setPosition(sf::Vector2f(
		this->y * this->crossLength + this->offsetX + 5.f,
		this->x * this->crossLength + this->offsetY + 32.f)
	);
	this->bar2.setSize(sf::Vector2f(this->crossLength - 2, size));
	this->bar2.setFillColor(color);
	this->bar2.setRotation(-45);
}

void Field::removeCross()
{
	this->bar1.setFillColor(sf::Color::Transparent);
	this->bar2.setFillColor(sf::Color::Transparent);
}

void Field::setDot()
{
	// Dot
	this->dot.setPosition(sf::Vector2f(
		this->y * this->crossLength + this->offsetX + this->crossLength / 2 - 8.f,
		this->x * this->crossLength + this->offsetY + this->crossLength / 2 - 8.f));
	this->dot.setRadius(8);
	this->dot.setFillColor(sf::Color::Transparent);
	this->dot.setFillColor(sf::Color(80, 80, 80));
}

void Field::removeDot()
{
	this->dot.setFillColor(sf::Color::Transparent);
}

void Field::reveal()
{
	this->hidden = false;
}

// Render
void Field::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->bar1);
	target->draw(this->bar2);
	target->draw(this->dot);
}