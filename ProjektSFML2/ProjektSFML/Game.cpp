#include "Game.h"

Game::Game()
{
	
	window = new sf::RenderWindow(sf::VideoMode(1024, 640), "POLIBUDA", sf::Style::Close | sf::Style::Resize);
	view = new sf::View(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1024, 640));
	level = new Level(GroundTextures);
	
}
Game::~Game()
{
	delete one;
}
void Game::loadTextures()
{
	playerTexture.loadFromFile("spritesheet3.png");

	tlo.loadFromFile("tlo3.jpg");
	one = new sf::Texture;

	one->loadFromFile("1.png");
	GroundTextures['G'] = one;

	one = new sf::Texture;
	one->loadFromFile("2.png");
	GroundTextures['D'] = one;

	one = new sf::Texture;
	one->loadFromFile("3.png");
	GroundTextures['X'] = one;

	one = new sf::Texture;
	one->loadFromFile("4.png");
	GroundTextures['B'] = one;
}
void Game::loadData()
{
	loadTextures();
}
bool Game::Run()
{
	return window->isOpen();
}

void Game::Update()
{
	window->setFramerateLimit(30);
	deltaTime = clock.restart().asSeconds();
	if (deltaTime > 1.0f / 20.0f)
		deltaTime = 1.0f / 20.0f;
	while (window->pollEvent(evnt)) {

		switch (evnt.type) {

		case sf::Event::Closed:
			window->close();
			break;
		}
	}

	player->Update(deltaTime);
	CheckCollision(direction, 1.0f);
	
}
void Game::Render()
{
	clock2.restart();
	Tlo.setTexture(tlo);
	view->setCenter(player->GetPosition());
	window->clear();
	window->draw(Tlo);
	window->setView(*view);

	Tlo.setPosition(view->getCenter().x - 512, view->getCenter().y - 320);
	

	sf::Font font;
	sf::Time elapsed1 = clock2.getElapsedTime();
	sf::Text licznik;
	std::ostringstream Zegar;
	licznik.setCharacterSize(35);
	licznik.setFillColor(sf::Color::Red);
	licznik.setFont(font);
	Zegar << "Czas: " << elapsed1.asSeconds();
	licznik.setString(Zegar.str());

	int score = 0;
	font.loadFromFile("font.ttf");
	std::ostringstream ssScore;
	ssScore << "Punkty ECTS: " << "[" << score << "]";
	sf::Text lblScore;
	lblScore.setCharacterSize(45);
	lblScore.setFillColor(sf::Color::Red);
	lblScore.setFont(font);
	lblScore.setString(ssScore.str());

	lblScore.setPosition(view->getCenter().x - 512, view->getCenter().y - 280);
	licznik.setPosition(view->getCenter().x - 512, view->getCenter().y - 180);

	for (int i = 0; i < level->Matrix.size(); i++)
	{
		for (int j = 0; j < level->Matrix[i].size(); j++)
		{
			window->draw(level->Matrix[i][j]);
		}
	}

	std::vector<Coin*> coinVec;
	Coin coin1({ 20, 20 });
	Coin coin2({ 20, 20 });
	Coin coin3({ 20, 20 });
	Coin coin4({ 20, 20 });
	coinVec.push_back(&coin1);
	coinVec.push_back(&coin2);
	coinVec.push_back(&coin3);
	coinVec.push_back(&coin4);

	coin1.setPos({ 420, 230 });
	coin2.setPos({ 580, 230 });
	coin3.setPos({ 360, 420 });
	coin4.setPos({ 220, 70 });

	coin1.drawTo(*window);
	coin2.drawTo(*window);
	coin3.drawTo(*window);
	coin4.drawTo(*window);

	player->Draw(*window);
	window->display();
}
void Game::CheckCollision(sf::Vector2f& direction, float p)
{
	float deltax;
	float deltay;
	float intersectX;
	float intersectY;


	for (size_t i = 0; i < this->level->Matrix.size(); i++)
	{
		for (size_t j = 0; j < this->level->Matrix[i].size(); j++)
		{


			sf::Vector2f thisposition = this->level->Matrix[i][j].getPosition();
			sf::Vector2f otherposition = this->player->GetPosition();
			sf::Vector2f thishalfsize(this->level->Matrix[i][j].getGlobalBounds().width / 2.0f, level->Matrix[i][j].getGlobalBounds().height / 2.0f);
			sf::Vector2f otherhalfsize = this->player->body.getSize() / 2.0f;
			bool t;

			deltax = otherposition.x - thisposition.x;
			deltay = otherposition.y - thisposition.y;

			intersectX = std::abs(deltax) - (otherhalfsize.x + thishalfsize.x);
			intersectY = std::abs(deltay) - (otherhalfsize.y + thishalfsize.y);

			if (intersectX < 0.0f && intersectY < 0.0f)
			{
				p = std::min(std::max(p, 0.0f), 1.0f);

				if (intersectX > intersectY)
				{
					if (deltax > 0.0f)
					{
						this->level->Matrix[i][j].move(intersectX * (1.0f - p), 0.0f);
						this->player->body.move(-intersectX * p, 0.0f);

						direction.x = 1.0f;
						direction.y = 0.0f;
					}
					else
					{
						this->level->Matrix[i][j].move(-intersectX * (1.0f - p), 0.0f);
						this->player->body.move(intersectX * p, 0.0f);

						direction.x = -1.0f;
						direction.y = 0.0f;
					}
				}
				else
				{
					if (deltay > 0.0f)
					{
						this->level->Matrix[i][j].move(0.0f, intersectY * (1.0f - p));
						this->player->body.move(0.0f, -intersectY * p);

						direction.x = 0.0f;
						direction.y = 1.0f;
					}
					else
					{
						this->level->Matrix[i][j].move(0.0f, -intersectY * (1.0f - p));
						this->player->body.move(0.0f, intersectY * p);

						direction.x = 0.0f;
						direction.y = -1.0f;
					}
				}

				t = true;

			}
			else {
				t = false;
			}
			if (t == true)
			{
				this->player->OnCollision(direction);
			}
		}

	}
}
