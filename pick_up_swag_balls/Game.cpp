#include "Game.h"


void Game::initVariables()
{
	this->endGame = false;
	this->spawnTimerMax = 10.f;
	this->spawnTimer = this->spawnTimerMax;
	this->maxSwagBalls = 10;
	this->points = 0;

}

void Game::initWindow()
{
	this->videoMode = sf::VideoMode(800, 600);
	this->window = new sf::RenderWindow(this->videoMode, "Game 2", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
}

void Game::initFont()
{
	if (!this->font.loadFromFile("Fonts/SHPinscher-Regular.otf")) {
		std::cout << "ERROR::GAME::INITFONT::FAILED TO LOAD FONT\n";
	}
	
}

void Game::initText()
{
	this->guiText.setFont(this->font);
	this->guiText.setFillColor(sf::Color::White);
	this->guiText.setCharacterSize(32);
	this->guiText.setPosition(5.f, 0.f);


	//endgame text
	this->endGameText.setFont(this->font);
	this->endGameText.setFillColor(sf::Color::Red);
	this->endGameText.setCharacterSize(60);
	this->endGameText.setPosition(sf::Vector2f(280,250));
	this->endGameText.setString("GAME OVER!");


}



// constructors and destructors
Game::Game()
{

	this->initVariables();
	this->initWindow();
	this->initFont();
	this->initText();
}

Game::~Game()
{
	delete this->window;
}

const bool& Game::getEndGame() const
{
	// TODO: insert return statement here
	return this->endGame;

}

const bool Game::running() const
{
	return this->window->isOpen(); //|| !this->endGame;
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->event)) {

		switch (this->event.type) {
		case sf::Event::Closed:
			this->window->close();
			break;

		case sf::Event::KeyPressed:

			if (this->event.key.code == sf::Keyboard::Escape) {
				this->window->close();

			}

			break;

		}

	}
}

void Game::spawnSwagBalls()
{
	// timer
	if (this->spawnTimer < this->spawnTimerMax) {
		this->spawnTimer += 1.f;
	}
	else {

		if (this->swagBalls.size() < this->maxSwagBalls) {

			this->swagBalls.push_back(SwagBall(*this->window, this->randBallType()));

		}

		this->spawnTimer = 0.f;
	}
}

const int Game::randBallType() const
{
	int type = SwagBallTypes::DEFAULT;

	int randValue = rand() % 100 + 1;

	if (randValue > 60 && randValue < 80) {
		type = SwagBallTypes::DAMAGING;
	}

	else if (randValue > 80 && randValue <= 100) {
		type = SwagBallTypes::HEALING;
	}

	return type;
}

void Game::updatePlayer()
{
	this->player.update(this->window);

	if (this->player.getHp() <= 0) {
		this->endGame = true;
	}

}

void Game::updateCollision()
{
	//check collision
	for (size_t i = 0; i < this->swagBalls.size(); i++) {

		if (this->player.getShape().getGlobalBounds().intersects(this->swagBalls[i].getShape().getGlobalBounds())) {

			switch (this->swagBalls[i].getType())
			{
			case SwagBallTypes::DEFAULT:
				// add point
				this->points++;
				break;

			case SwagBallTypes::DAMAGING:
				this->player.takeDamage(1);
				break;

			case SwagBallTypes::HEALING:
				this->player.gainHealth(1);
				break;
			}


			// remove ball
			this->swagBalls.erase(this->swagBalls.begin() + static_cast<int>(i));
		}

	}


}

void Game::updateGui()
{

	// converts anything to string
	std::stringstream ss;
	ss << " - Points: " << this->points << "\n"
		<< " - Health: " << this->player.getHp() << " / " << this->player.getHpMax() << "\n";
	
	this->guiText.setString(ss.str());
}

void Game::update()
{
	this->pollEvents();


	if (!this->endGame)
	{

		this->spawnSwagBalls();
		this->updateCollision();

		this->updateGui();
		this->updatePlayer();
	}
}

void Game::renderGui(sf::RenderTarget* target)
{
	target->draw(guiText);
}

void Game::render()
{
	this->window->clear();


	// render stuff
	for (auto ball : this->swagBalls) {
		ball.render(this->window);
	}
	this->player.render(this->window);


	// render gui
	this->renderGui(this->window);


	// render end text

	if (this->endGame) {
		this->window->draw(this->endGameText);
	}
	this->window->draw(this->endGameText);



	this->window->display();
}
