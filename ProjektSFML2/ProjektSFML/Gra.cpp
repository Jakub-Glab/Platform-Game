#include "Gra.h"


Gra::Gra()
{
	window = new sf::RenderWindow(sf::VideoMode(1024, 640), "POLIBUDA", sf::Style::Close | sf::Style::Resize);
	loadData();
	view = new sf::View(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1024, 640));
	level = new Level(GroundTextures);
	player = new Player(&playerTexture, sf::Vector2u(3, 8), 0.1f, 200.0f, 320.0f);
	// old coin:  coin = new Coin(&coinTexture, sf::Vector2u(1, 7), 0.2f, sf::Vector2f(420, 210));
	// old coin:  coin1 = new Coin(&coinTexture, sf::Vector2u(1, 7), 0.2f, sf::Vector2f(300, 210));
	coin = new Coin(CoinTextures);
	ST_level = new STLevel(ST_textures);

}
Gra::~Gra()
{
	delete wall;
	delete grass;
	delete stone;
	delete box;
	delete coin;
	delete player;
	delete view;
}
void Gra::loadTextures()
{
	if (!playerTexture.loadFromFile("spritesheet3.png"))
	{
		std::cout << "Problem z zaladowaniem tekstury gracza nr";
	}

	if (!coinsound.loadFromFile("coin.wav"))
	{
		std::cout << "Problem z zaladowaniem dzwieku nr. 1";
	}
	if (!jumpSound1.loadFromFile("jump1.ogg"))
	{
		std::cout << "Problem z zaladowaniem dzwieku nr. 2";

	}
	if (!jumpSound2.loadFromFile("jump2.ogg"))
	{
		std::cout << "Problem z zaladowaniem dzwieku nr. 3";
	}

	/*if (!coinTexture.loadFromFile("CoinSheet.png"))
	{
		std::cout << "Problem z zaladowaniem tekstury coin";
	}*/

	sound1.setBuffer(coinsound);
	jump_sound1.setBuffer(jumpSound1);
	jump_sound2.setBuffer(jumpSound2);

	tlo.loadFromFile("Textures/tlo4.jpg");

	grass = new sf::Texture;
	grass->loadFromFile("Textures/grass.png");
	ST_textures['G'] = grass;

	grass = new sf::Texture;
	grass->loadFromFile("Textures/grass2.png");
	ST_textures['2'] = grass;

	grass = new sf::Texture;
	grass->loadFromFile("Textures/grass3.png");
	ST_textures['3'] = grass;

	grass = new sf::Texture;
	grass->loadFromFile("Textures/grassCorner1.png");
	ST_textures['4'] = grass;

	grass = new sf::Texture;
	grass->loadFromFile("Textures/grassCorner2.png");
	ST_textures['5'] = grass;

	grass = new sf::Texture;
	grass->loadFromFile("Textures/grassfull.png");
	ST_textures['6'] = grass;

	water = new sf::Texture;
	water->loadFromFile("Textures/water.png");
	ST_textures['W'] = water;

	stone = new sf::Texture;
	stone->loadFromFile("Textures/2.png");
	GroundTextures['D'] = stone;

	wall = new sf::Texture;
	wall->loadFromFile("Textures/3.png");
	GroundTextures['X'] = wall;

	box = new sf::Texture;
	box->loadFromFile("Textures/4.png");
	GroundTextures['B'] = box;

	coinT = new sf::Texture;
	coinT->loadFromFile("Textures/coinP.png");
	CoinTextures['C'] = coinT;
}
void Gra::loadData()
{
	Chmurki();
	loadTextures();
	//TworzCoin();
	Czas();
	wysPunkty();
}
void Gra::Czas()
{
	Zegar.clear();
	clock2.restart();
	c += elapsed1.asSeconds();
	Zegar << "Czas: " << c;
}
bool Gra::Run()
{
	return window->isOpen();
}
void Gra::wysPunkty()
{
	if (score == 0) ssScore << "Punkty ECTS: " << "[" << score << "]";
}
void Gra::Update()
{

	elapsed3 = clock3.restart();



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

		if (evnt.type == sf::Event::KeyReleased)
		{
			if (evnt.key.code == sf::Keyboard::Space)
			{
				jump_sound1.play();
				player->DoubleJump();
			}
			if (evnt.key.code == sf::Keyboard::W)
			{
				jump_sound1.play();
			}
		}

	}
	for (size_t i = 0; i < alien.size(); i++)
	{
		alien[i]->Animuj(elapsed3);
	}

	// old coin:  coin->Update(deltaTime);
	// old coin:  coin1->Update(deltaTime);
	player->Update(deltaTime);
	CheckCollision(direction, 1.0f);
	CheckCollisionST(direction2, 1.0f);
	CoinCollision(direction3, 1.0f);
}
/*void Gra::TworzCoin()
{
	// old coin:  coinVec.push_back(coin);
	// old coin:  coinVec.push_back(coin1);
}*/
void Gra::Chmurki()
{
	for (int i = 0; i < 5; i++)
	{
		alien.emplace_back(std::make_unique<Duch>("Textures/chmurka.png"));
		float pleaceX;
		float pleaceY;
	

		for (size_t i = 0; i < alien.size(); i++)
		{
			
				pleaceX = rand() % 2400;
				pleaceY = rand() % 240 - 450;
			
			alien[i]->setPosition(pleaceX, pleaceY);
		}


	}
}
void Gra::Render()
{

	Tlo.setTexture(tlo);
	view->setCenter(player->GetPosition());
	window->clear();
	window->draw(Tlo);
	window->setView(*view);
	Tlo.setPosition(view->getCenter().x - 512, view->getCenter().y - 320);
//	Chmurki();
	
	for (size_t i = 0; i < alien.size(); i++)
	{
		window->draw(*alien[i]);
	}
	player->Draw(*window);
	for (int i = 0; i < level->Matrix.size(); i++)
	{
		for (int j = 0; j < level->Matrix[i].size(); j++)
		{
			window->draw(level->Matrix[i][j]);
		}
	}
	for (int i = 0; i < ST_level->MatrixST.size(); i++)
	{
		for (int j = 0; j < ST_level->MatrixST[i].size(); j++)
		{
			window->draw(ST_level->MatrixST[i][j]);
		}
	}
	for (int i = 0; i < coin->MatrixCoin.size(); i++)
	{
		for (int j = 0; j < coin->MatrixCoin[i].size(); j++)
		{
			window->draw(coin->MatrixCoin[i][j]);
		}
	}
	

	// old coin:  coin->Draw(*window);
	// old coin:  coin1->Draw(*window);
	Licznik();
	
	window->display();
}
/*bool Gra::isCollidingWithCoin(std::vector<Coin*>& coinVec)
{

	if (this->player->body.getGlobalBounds().intersects(this->coin->ects.getGlobalBounds())) {
		sound1.play();
		return true;
	}
	return false;

}*/
void Gra::Licznik()
{
	font.loadFromFile("font.ttf");
	/*
	licznik.setCharacterSize(35);
	licznik.setFillColor(sf::Color::Red);
	licznik.setFont(font);
	licznik.setString(Zegar.str());
	licznik.setPosition(view->getCenter().x - 512, view->getCenter().y - 180);
	*/
	Score.setCharacterSize(45);
	Score.setFillColor(sf::Color::Red);
	Score.setFont(font);
	Score.setString(ssScore.str());
	Score.setPosition(view->getCenter().x - 512, view->getCenter().y - 280);
	/* old coin:  
	for (int i = 0; i < coinVec.size(); i++) {
		if (isCollidingWithCoin(coinVec)) {
			coinVec.erase(coinVec.begin() + i);
			score++;
			ssScore.str("");
			ssScore << "Punkty ECTS: " << "[" << score << "]";
			Score.setString(ssScore.str());
		}
	}
	*/
	window->draw(Score);
	window->draw(licznik);

}
void Gra::CheckCollision(sf::Vector2f& direction, float p)
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
			sf::Vector2f thishalfsize(this->level->Matrix[i][j].getGlobalBounds().width / 2.0f, (level->Matrix[i][j].getGlobalBounds().height) / 2.0f);
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
void Gra::CheckCollisionST(sf::Vector2f& direction, float p)
{
	
	float deltax;
	float deltay;
	float intersectX;
	float intersectY;

	for (size_t i = 0; i < this->ST_level->MatrixST.size(); i++)
	{
		for (size_t j = 0; j < this->ST_level->MatrixST[i].size(); j++)
		{
			sf::Vector2f thisposition = this->ST_level->MatrixST[i][j].getPosition();
			sf::Vector2f otherposition = this->player->GetPosition();
			sf::Vector2f thishalfsize(this->ST_level->MatrixST[i][j].getGlobalBounds().width / 2.0f, (ST_level->MatrixST[i][j].getGlobalBounds().height - 7) / 2.0f);
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
						this->ST_level->MatrixST[i][j].move(intersectX * (1.0f - p), 0.0f);
						this->player->body.move(-intersectX * p, 0.0f);

						direction.x = 1.0f;
						direction.y = 0.0f;
					}
					else
					{
						this->ST_level->MatrixST[i][j].move(-intersectX * (1.0f - p), 0.0f);
						this->player->body.move(intersectX * p, 0.0f);

						direction.x = -1.0f;
						direction.y = 0.0f;
					}
				}
				else
				{
					if (deltay > 0.0f)
					{
						this->ST_level->MatrixST[i][j].move(0.0f, intersectY * (1.0f - p));
						this->player->body.move(0.0f, -intersectY * p);

						direction.x = 0.0f;
						direction.y = 1.0f;
					}
					else
					{
						this->ST_level->MatrixST[i][j].move(0.0f, -intersectY * (1.0f - p));
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
void Gra::CoinCollision(sf::Vector2f& direction, float p)
{
	
	float deltax;
	float deltay;
	float intersectX;
	float intersectY;


	for (size_t i = 0; i < this->coin->MatrixCoin.size(); i++)
	{
		for (size_t j = 0; j < this->coin->MatrixCoin[i].size(); j++)
		{


			sf::Vector2f thisposition = this->coin->MatrixCoin[i][j].getPosition();
			sf::Vector2f otherposition = this->player->GetPosition();
			sf::Vector2f thishalfsize(this->coin->MatrixCoin[i][j].getGlobalBounds().width / 2.0f, coin->MatrixCoin[i][j].getGlobalBounds().height / 2.0f);
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
						this->coin->MatrixCoin[i][j].move(intersectX * (1.0f - p), 0.0f);
						this->player->body.move(-intersectX * p, 0.0f);

						direction.x = 1.0f;
						direction.y = 0.0f;
					}
					else
					{
						this->coin->MatrixCoin[i][j].move(-intersectX * (1.0f - p), 0.0f);
						this->player->body.move(intersectX * p, 0.0f);

						direction.x = -1.0f;
						direction.y = 0.0f;
					}
				}
				else
				{
					if (deltay > 0.0f)
					{
						this->coin->MatrixCoin[i][j].move(0.0f, intersectY * (1.0f - p));
						this->player->body.move(0.0f, -intersectY * p);

						direction.x = 0.0f;
						direction.y = 1.0f;
					}
					else
					{
						this->coin->MatrixCoin[i][j].move(0.0f, -intersectY * (1.0f - p));
						this->player->body.move(0.0f, intersectY * p);

						direction.x = 0.0f;
						direction.y = -1.0f;
					}
				}
				//return true;
				t = true;

			}
			else {
				t = false;
			}
			if (t == true)
			{
				score++;
				ssScore.str("");
				ssScore << "Punkty ECTS: " << score;
				Score.setString(ssScore.str());
				coin->MatrixCoin[i].erase(coin->MatrixCoin[i].begin() + j, coin->MatrixCoin[i].begin() + j + 1);
				sound1.play();

			}
		}

	}
}
