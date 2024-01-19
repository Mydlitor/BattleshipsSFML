#include "Field.h"

Field::Field(int x, int y, float offsetX, float offsetY, float size, bool status,
	sf::Color borderColor, sf::Color emptyColor, sf::Color shipColor, sf::Color hitColor, sf::Color sankColor, sf::Color missColor)
{
	this->hidden = status;

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

	// Cross
	this->bar1.setPosition(sf::Vector2f(y * size + offsetX + 8.f, x * size + offsetY + 5.f));
	this->bar1.setSize(sf::Vector2f(size - 2.f, size / 8));
	this->bar1.setFillColor(sf::Color::Transparent);
	this->bar1.setRotation(45);

	this->bar2.setPosition(sf::Vector2f(y * size + offsetX + 5.f, x * size + offsetY + 32.f));
	this->bar2.setSize(sf::Vector2f(size - 2.f, size / 8));
	this->bar2.setFillColor(sf::Color::Transparent);
	this->bar2.setRotation(-45);
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
			break;

		case 1: // SHIP
			this->shape.setFillColor(this->shipColor);
			break;

		case 2: // HIT
			this->shape.setFillColor(this->shipColor);
			setCross();
			break;

		case 3: // SANK
			this->shape.setFillColor(this->sankColor);
			setCross();
			break;

		case 4: // MISS
			this->shape.setFillColor(this->missColor);
			break;

		case 9:
			this->shape.setFillColor(sf::Color::Magenta);
			break;

		default:
			this->shape.setFillColor(sf::Color::White);
			break;
		}
}

void Field::setCross()
{
	this->bar1.setFillColor(sf::Color::Red);
	this->bar2.setFillColor(sf::Color::Red);
}

void Field::reveal()
{
	this->hidden = false;
}

void Field::setHovered(bool hover)
{
	//this->hovered = hover;
	
}

// Accessors
const bool Field::isHidden() const
{
	return hidden;
}

const bool Field::isHovered() const {
	return hovered;
}

const bool Field::isMouseOverShape(const sf::Vector2f mousePos) const
{
	return this->shape.getGlobalBounds().contains(mousePos);
}

const sf::RectangleShape Field::getShape() const
{
	return shape;
}

// Render
void Field::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->bar1);
	target->draw(this->bar2);
}
