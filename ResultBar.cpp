#include "ResultBar.h"

ResultBar::ResultBar(sf::RenderWindow& window, sf::Font* font, int winner)
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
	this->container.setPosition(0, 40.f);
	this->container.setFillColor(sf::Color(8, 98, 201));

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(40);
}

ResultBar::~ResultBar()
{
	
}

void ResultBar::updateResult(int winner)
{
	if (winner == 1) this->textContent = "Congratulations! You won!";
	else if (winner == 2) this->textContent = "Unfortunately, you were defeated by the opponent.";

	this->text.setString(this->textContent);
	this->text.setPosition(
		this->container.getPosition().x + (this->container.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->container.getPosition().y + (this->container.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f - 10.f
	);
}

void ResultBar::update(const sf::Vector2f mousePos)
{
}

void ResultBar::render(sf::RenderTarget& target)
{
	target.draw(this->background);
	target.draw(this->container);
	target.draw(this->text);	
}
