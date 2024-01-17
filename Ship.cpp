#include "Ship.h"

Ship::Ship(float x, float y, float width, float height,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, sf::Color placedColor)
{
	this->shipState = SHIP_IDLE;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	
	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;
	this->placedColor = placedColor;

	this->shape.setFillColor(this->idleColor);
}

Ship::~Ship()
{
}

// Accessor
const bool Ship::isPressed() const
{
	if (this->shipState == SHIP_ACTIVE)
		return true;

	return false;
}

const bool Ship::isPlaced() const
{
	if (this->shipState == SHIP_PLACED)
		return true;
	return false;
}

sf::RectangleShape Ship::getShape()
{
	return this->shape;
}

void Ship::setPlaced(short unsigned state)
{
	this->shipState = state;
}

// Functions
void Ship::update(const sf::Vector2f mousePos)
{
	/*Update the booleams for hover and pressed*/

	// Idle
	if (this->shipState != SHIP_PLACED)
	{
		this->shipState = SHIP_IDLE;

		// Hover
		if (this->shape.getGlobalBounds().contains(mousePos))
		{
			this->shipState = SHIP_HOVER;

			// Pressed
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				this->shipState = SHIP_ACTIVE;
			}
		}
	}

	switch (this->shipState)
	{
	case SHIP_IDLE:
		this->shape.setFillColor(this->idleColor);
		break;

	case SHIP_HOVER:
		this->shape.setFillColor(this->hoverColor);
		break;

	case SHIP_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		break;

	case SHIP_PLACED:
		this->shape.setFillColor(this->placedColor);
		break;

	default:
		this->shape.setFillColor(sf::Color::Red);
		break;
	}
}

void Ship::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
