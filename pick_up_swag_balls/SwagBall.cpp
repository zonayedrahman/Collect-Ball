#include "SwagBall.h"


void SwagBall::initShape(sf::RenderWindow& window)
{

	this->shape.setRadius(static_cast<float>(rand() % 10 + 10));
	sf::Color color;

	switch (this->type) {
	case DEFAULT:
		color = sf::Color(static_cast<sf::Uint8>(rand() % 255 + 1), static_cast<sf::Uint8>(rand() % 255 + 1), static_cast<sf::Uint8>(rand() % 255 + 1));
		break;
	case DAMAGING:
		color = sf::Color::Red;
		this->shape.setOutlineColor(sf::Color::White);
		this->shape.setOutlineThickness(2.f);
		break;

	case HEALING:
		color = sf::Color::Green;
		this->shape.setOutlineColor(sf::Color::White);
		this->shape.setOutlineThickness(2.f);
		break;
	}
	
	this->shape.setFillColor(color);
	this->shape.setPosition(sf::Vector2f(
		static_cast<float>(rand() % window.getSize().x - this->shape.getGlobalBounds().width),
		static_cast<float>(rand() % window.getSize().y - this->shape.getGlobalBounds().height)
	));
}

SwagBall::SwagBall(sf::RenderWindow& window, int type)
	: type(type)
{
	this->initShape(window);

}

SwagBall::~SwagBall()
{
}

// accessors




const sf::CircleShape SwagBall::getShape() const
{
	return this->shape;
}

const int& SwagBall::getType() const
{
	// TODO: insert return statement here
	return this->type;
}

void SwagBall::update()
{
}

void SwagBall::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}


