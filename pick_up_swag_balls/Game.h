#pragma once


#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


#include "Player.h"
#include "SwagBall.h"

#include <vector>
#include <sstream>



class Game
{
private:
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	bool endGame;
	sf::Event event;

	Player player;
	int points;

	sf::Font font;
	sf::Text guiText;
	sf::Text endGameText;

	std::vector<SwagBall> swagBalls;


	float spawnTimerMax;
	float spawnTimer;
	int maxSwagBalls;


	void initVariables();
	void initWindow();
	void initFont();
	void initText();

public:

	// contructors and destructors
	Game();
	~Game();


	// accessors
	const bool& getEndGame() const;

	// modifiers

	// functions
	const bool running() const;
	void pollEvents();


	void spawnSwagBalls();
	const int randBallType() const;


	void updatePlayer();
	void updateCollision();
	void updateGui();
	void update();


	void renderGui(sf::RenderTarget* target);
	void render();




};

