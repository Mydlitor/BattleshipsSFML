#include "ResultBar.h"

ResultBar::ResultBar(sf::RenderWindow& window)
{
	this->background.setSize(sf::Vector2f(
		static_cast<float>(window.getSize().x),
		static_cast<float>(window.getSize().y)
	));
	this->background.setFillColor(sf::Color(0, 0, 0, 20));


	this->container.setSize(sf::Vector2f(
		static_cast<float>(window.getSize().x), 
		100.f
	));
	this->container.setPosition(
		0,
		40.f
	);
	this->container.setFillColor(sf::Color(8, 98, 201));
}

ResultBar::~ResultBar()
{

}

void ResultBar::update(const sf::Vector2f mousePos)
{

}

void ResultBar::render(sf::RenderTarget& target)
{
	target.draw(this->background);
	target.draw(this->container);
}
