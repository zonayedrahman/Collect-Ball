#pragma once


#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


enum SwagBallTypes {
	DEFAULT = 0,
	DAMAGING,
	HEALING,
	NROFTYPES
};


class SwagBall
{

private:
	sf::CircleShape shape;
	int type;


	void initShape(sf::RenderWindow& window);


public:

	SwagBall(sf::RenderWindow& window, int type);
	virtual ~SwagBall();

	//accessor
	const sf::CircleShape getShape() const;
	const int& getType() const;
	void update();
	void render(sf::RenderTarget* target);

};

