#include "Player.h"

void Player::initVariables()
{

	this->movementSpeed = 5.f;
	this->hpMax = 10;
	this->hp = this->hpMax;
	
}

void Player::initShape()
{
	this->shape.setFillColor(sf::Color::Green);
	this->shape.setSize(sf::Vector2f(50.f, 50.f));

}

Player::Player(float x, float y)
{

	this->shape.setPosition(x, y);


	this->initVariables();
	this->initShape();
}

Player::~Player()
{
}

const sf::RectangleShape& Player::getShape() const
{
	// TODO: insert return statement here
	return this->shape;
}

const int& Player::getHp() const
{
	// TODO: insert return statement here
	return this->hp;
}

const int& Player::getHpMax() const
{
	// TODO: insert return statement here
	return this->hpMax;
}

void Player::takeDamage(const int damage)
{
	if (this->hp > 0) {
		this->hp -= damage;
	}

	if (this->hp < 0) {
		this->hp = 0;
	}
}

void Player::gainHealth(const int gain)
{
	if (this->hp < this->hpMax) {
		this->hp += gain;
	}

	if (this->hp > this->hpMax) {
		this->hp = this->hpMax;
	}
}

void Player::updateInput()
{
	// keyboard input
	
	//std::cout << this->shape.getPosition().x << " " << this->shape.getPosition().y << std::endl;

	// left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		this->shape.move(-this->movementSpeed, 0.f);


	}

	// right
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		this->shape.move(this->movementSpeed, 0.f);
	}

	// up
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		this->shape.move(0.f , -this->movementSpeed);
	}

	//down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		this->shape.move(0.f, this->movementSpeed);
	}


}

void Player::updateWindowBoundsCollision(const sf::RenderTarget* target)
{

	//sf::Vector2f playerPos = this->shape.getPosition();

	// left
	if (this->shape.getGlobalBounds().left <= 0.f) {
		this->shape.setPosition(0.f, this->shape.getGlobalBounds().top);
	}
	//right
	if (this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width >= target->getSize().x) {
		this->shape.setPosition(target->getSize().x - this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().top);
	}

	// top
	if (this->shape.getGlobalBounds().top <= 0.f) {
		this->shape.setPosition(this->shape.getGlobalBounds().left, 0.f);
	}
	if (this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height >= target->getSize().y) {
		this->shape.setPosition(this->shape.getGlobalBounds().left, target->getSize().y - this->shape.getGlobalBounds().height);
	}

	//bottom

}

void Player::update(sf::RenderTarget* target)
{


	this->updateInput();
	// Window bounds collisions
	this->updateWindowBoundsCollision(target);



}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}

