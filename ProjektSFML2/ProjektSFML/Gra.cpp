#include "Gra.h"


Gra::Gra(int win)
{
	window = new sf::RenderWindow(sf::VideoMode(1024, 640), "Gra SFML", sf::Style::Close | sf::Style::Resize);
	loadData();
	view = new sf::View(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1024, 640));
	level = new Level(GroundTextures);
	levelE = new LevelE(GroundTexturesE);
	player = new Player(&playerTexture, sf::Vector2u(3, 8));
	ST_level = new STLevel(ST_textures);
	EnemiesLoad();
	TworzCoin();
	start = std::clock();
	wygryw = win;
}
Gra::~Gra()
{
	delete wall;
	delete grass;
	delete stone;
	delete box;
	delete player;
	delete view;
}
void Gra::loadTextures()
{
	if (!playerTexture.loadFromFile("Textures/player_texture.png")) { std::cout << "Problem z zaladowaniem tekstury gracza"; }
	if (!enemyTexture2.loadFromFile("Textures/enemy_texture.png")) { std::cout << "Problem z zaladowaniem tekstury wroga"; }
	if (!coinsound.loadFromFile("Sounds/coin.wav")) { std::cout << "Problem z zaladowaniem dzwieku nr. 1"; }
	if (!jumpSound1.loadFromFile("Sounds/jump1.ogg")) { std::cout << "Problem z zaladowaniem dzwieku nr. 2"; }
	if (!jumpSound2.loadFromFile("Sounds/jump2.ogg")) { std::cout << "Problem z zaladowaniem dzwieku nr. 3"; }
	if (!damageSound.loadFromFile("Sounds/damage.wav")) { std::cout << "Problem z zaladowaniem dzwieku nr. 4"; }
	if (!tlo.loadFromFile("Textures/tlo4.jpg")); {std::cout << "Problem z zaladowaniem grafiki tla"; }
	if (!font.loadFromFile("Fonts/font.ttf")) { std::cout << "Blad z zaladowaniem czcionki!!"; }
	if (!icon.loadFromFile("Textures/ikona_gra.png")) { std::cout << "Blad z zaladowaniem ikony!!"; }
	if (!coinTexture.loadFromFile("Textures/CoinSheet.png")) { std::cout << "Problem z zaladowaniem tekstury coina"; }
	sound1.setBuffer(coinsound);
	jump_sound1.setBuffer(jumpSound1);
	jump_sound2.setBuffer(jumpSound2);
	damage.setBuffer(damageSound);


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

	grass = new sf::Texture;
	grass->loadFromFile("Textures/dirt.png");
	GroundTextures['7'] = grass;

	water = new sf::Texture;
	water->loadFromFile("Textures/water.png");
	ST_textures['W'] = water;

	stone = new sf::Texture;
	stone->loadFromFile("Textures/stone.png");
	GroundTextures['D'] = stone;

	wall = new sf::Texture;
	wall->loadFromFile("Textures/3.png");
	GroundTextures['X'] = wall;

	e_wall = new sf::Texture;
	wall->loadFromFile("Textures/3.png");
	GroundTexturesE['F'] = e_wall;

	box = new sf::Texture;
	box->loadFromFile("Textures/box.png");
	GroundTextures['B'] = box;


	Oceny.setFillColor(sf::Color::Green);

}
void Gra::loadData()
{
	Chmurki();
	loadTextures();
	//TworzCoin();
	Czas();
	wysPunkty();
	wysZycie();

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
void Gra::wygrana()
{
	sf::RenderWindow window2(sf::VideoMode(800, 400), "Wygrana");
	sf::Texture texture3;
	texture3.loadFromFile("Textures/tlo_wygrana.png");
	sf::Sprite sprite3;
	sprite3.setTexture(texture3);
	sprite3.setPosition(0, 0);
	sf::Image icon;
	icon.loadFromFile("Textures/ikona_gra.png");
	window2.setIcon(64, 64, icon.getPixelsPtr());
	sf::Event evnt;
	sf::Font font2;
	if (!font2.loadFromFile("Fonts/font.ttf")) { std::cout << "Blad z zaladowaniem czcionki!!"; }
	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	sf::Text Czas_t;
	sf::Text Wynik_t;
	std::ostringstream Czas;
	std::ostringstream Wynik;
	Czas << duration << " sekund";
	Czas_t.setCharacterSize(35);
	Czas_t.setFillColor(sf::Color::Red);
	Czas_t.setFont(font);
	Czas_t.setString(Czas.str());
	Czas_t.setPosition(400, 185);
	float final_score = (zycie * (duration))*100;
	Wynik << final_score;
	Wynik_t.setCharacterSize(35);
	Wynik_t.setFillColor(sf::Color::Blue);
	Wynik_t.setFont(font);
	Wynik_t.setString(Wynik.str());
	Wynik_t.setPosition(400, 236);
	while (window2.isOpen())
	{
		while (window2.pollEvent(evnt)) {

			switch (evnt.type) {

			case sf::Event::Closed:
				window2.close();
				break;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window2.close();
		}


		window2.clear();
		window2.draw(sprite3);
		if (zycie == 4)
		{
			sf::Text Koniec("Bdb", font2);
			Koniec.setFillColor(sf::Color::Green);
			Koniec.setCharacterSize(35);
			Koniec.setPosition(400, 135);
			window2.draw(Koniec);
		}
		if (zycie == 3.75) {
			sf::Text Koniec("Bdb -", font2);
			Koniec.setFillColor(sf::Color::Green);
			Koniec.setCharacterSize(35);
			Koniec.setPosition(400, 135);
			window2.draw(Koniec);
		}
		if (zycie == 3.5) {
			sf::Text Koniec("Db +", font2);
			Koniec.setFillColor(sf::Color::Green);
			Koniec.setCharacterSize(35);
			Koniec.setPosition(400, 135);
			window2.draw(Koniec);
		}
		if (zycie == 3.25) {
			sf::Text Koniec("Db ", font2);
			Koniec.setFillColor(sf::Color::Green);
			Koniec.setCharacterSize(35);
			Koniec.setPosition(400, 135);
			window2.draw(Koniec);
		}
		if (zycie == 3) {
			sf::Text Koniec("Db ", font2);
			Koniec.setFillColor(sf::Color::Green);
			Koniec.setCharacterSize(35);
			Koniec.setPosition(400, 135);
			window2.draw(Koniec);
		}
		if (zycie == 2.75) {
			sf::Text Koniec("Db -", font2);
			Koniec.setFillColor(sf::Color::Yellow);
			Koniec.setCharacterSize(35);
			Koniec.setPosition(400, 135);
			window2.draw(Koniec);
		}
		if (zycie == 2.5) {
			sf::Text Koniec("Dst +", font2);
			Koniec.setFillColor(sf::Color::Yellow);
			Koniec.setCharacterSize(35);
			Koniec.setPosition(400, 135);
			window2.draw(Koniec);
		}
		if (zycie == 2.25) {
			sf::Text Koniec("Dst ", font2);
			Koniec.setFillColor(sf::Color::Yellow);
			Koniec.setCharacterSize(35);
			Koniec.setPosition(400, 135);
			window2.draw(Koniec);
		}
		if (zycie == 2) {
			sf::Text Koniec("Dst ", font2);
			Koniec.setFillColor(sf::Color::Yellow);
			Koniec.setCharacterSize(35);
			Koniec.setPosition(400, 135);
			window2.draw(Koniec);
		}
		if (zycie == 1.75) {
			sf::Text Koniec("Dst -", font2);
			Koniec.setFillColor(sf::Color::Yellow);
			Koniec.setCharacterSize(35);
			Koniec.setPosition(400, 135);
			window2.draw(Koniec);
		}
		window2.draw(Czas_t);
		window2.draw(Wynik_t);
		window2.display();
	}
}
void Gra::przegrana()
{
	sf::RenderWindow window2(sf::VideoMode(800, 400), "Przegrana");
	sf::Texture texture3;
	texture3.loadFromFile("Textures/tlo_przegrana.png");
	sf::Sprite sprite3;
	sprite3.setTexture(texture3);
	sprite3.setPosition(0, 0);
	sf::Image icon;
	icon.loadFromFile("Textures/ikona_gra.png");
	window2.setIcon(64, 64, icon.getPixelsPtr());
	sf::Event evnt;
	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	while (window2.isOpen())
	{
		while (window2.pollEvent(evnt)) {

			switch (evnt.type) {

			case sf::Event::Closed:
				window2.close();
				break;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window2.close();
		}
		window2.clear();
		window2.draw(sprite3);
		window2.display();
	}
}
void Gra::wysZycie()
{
	if (zycie > 4) { zycie = 4; }
	if (zycie == 4) { ssOceny << " Bdb "; Oceny.setFillColor(sf::Color::Green); }
	if (zycie == 3.75) { ssOceny << " Bdb - "; Oceny.setFillColor(sf::Color::Green); }
	if (zycie == 3.5) { ssOceny << " Db + "; Oceny.setFillColor(sf::Color::Green); }
	if (zycie == 3.25) { ssOceny << " Db "; Oceny.setFillColor(sf::Color::Green); }
	if (zycie == 3) { ssOceny << " Db "; Oceny.setFillColor(sf::Color::Green); }
	if (zycie == 2.75) { ssOceny << " Db - "; Oceny.setFillColor(sf::Color::Yellow); }
	if (zycie == 2.5) { ssOceny << " Dst + "; Oceny.setFillColor(sf::Color::Yellow); }
	if (zycie == 2.25) { ssOceny << " Dst "; Oceny.setFillColor(sf::Color::Yellow); }
	if (zycie == 2) { ssOceny << " Dst "; Oceny.setFillColor(sf::Color::Yellow); }
	if (zycie == 1.75) { ssOceny << " Dst - "; Oceny.setFillColor(sf::Color::Yellow); }
	if (zycie <= 1.5)
	{
		ssOceny << " ndst ";
		Oceny.setFillColor(sf::Color::Red);
		window->close();
		przegrana();
	}
}
void Gra::wysPunkty()
{
	if (score == 0) ssScore << "Punkty ECTS: " << score;

}
void Gra::Update()
{

	elapsed3 = clock3.restart();

	window->setFramerateLimit(60);
	deltaTime = clock.restart().asSeconds();
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
	for (size_t i = 0; i < przeciwnik.size(); i++)
	{
		przeciwnik[i]->Update(deltaTime);
	}
	for (size_t i = 0; i < coin.size(); i++)
	{
		coin[i]->Update(deltaTime);
	}
	PlayerCollision(direction);
	PlayerCollisionST(direction2);
	WrogowieCollisionST(direction2);
	WrogowieCollision(direction2);
	CoinCollision(direction3);
	CombatCollision2(direction);
	enemyWall(direction);
}
void Gra::TworzCoin()
{
	std::ifstream file("Maps/coinMap.txt");
	std::string charLine;
	std::vector<char> mapLine;
	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, charLine);
			for (int i = 0; i < charLine.length(); i++)
			{
				mapLine.push_back(charLine[i]);
			}
			CoinLocation.push_back(mapLine);
			mapLine.clear();
			charLine.clear();
		}
	}

	for (int i = 0; i < CoinLocation.size(); i++)
	{
		for (int j = 0; j < EnemiesLocation[i].size(); j++)
		{
			if (EnemiesLocation[i][j] == 'C')
			{
				coin.emplace_back(std::make_unique<Coiny>(&coinTexture, sf::Vector2u(1, 7), (j * 64), (i * 64)));
			}
		}

	}
}
void Gra::Chmurki()
{
	for (int i = 0; i < 10; i++)
	{
		alien.emplace_back(std::make_unique<Duch>("Textures/chmurka.png"));
		float pleaceX;
		float pleaceY;


		for (size_t i = 0; i < alien.size(); i++)
		{

			pleaceX = rand() % 9600;
			pleaceY = rand() % 890 - 600;

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

	window->setIcon(64, 64, icon.getPixelsPtr());

	for (size_t i = 0; i < alien.size(); i++)
	{
		window->draw(*alien[i]);
	}
	for (size_t i = 0; i < przeciwnik.size(); i++)
	{
		przeciwnik[i]->Draw(*window);
	}
	for (size_t i = 0; i < coin.size(); i++)
	{
		coin[i]->Draw(*window);
	}
	player->Draw(*window);

	for (int i = 0; i < ST_level->MatrixST.size(); i++)
	{
		for (int j = 0; j < ST_level->MatrixST[i].size(); j++)
		{
			window->draw(ST_level->MatrixST[i][j]);
		}
	}
	for (int i = 0; i < level->Matrix.size(); i++)
	{
		for (int j = 0; j < level->Matrix[i].size(); j++)
		{
			window->draw(level->Matrix[i][j]);
		}
	}
	;
	Licznik();

	window->display();
}
void Gra::EnemiesLoad()
{
	std::ifstream file("Maps/mapaEnemies.txt");
	std::string charLine;
	std::vector<char> mapLine;
	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, charLine);
			for (int i = 0; i < charLine.length(); i++)
			{
				mapLine.push_back(charLine[i]);
			}
			EnemiesLocation.push_back(mapLine);
			mapLine.clear();
			charLine.clear();
		}
	}
	
		for (int i = 0; i < EnemiesLocation.size(); i++)
		{
			for (int j = 0; j < EnemiesLocation[i].size(); j++)
			{
				if (EnemiesLocation[i][j] == 'E')
				{
					przeciwnik.emplace_back(std::make_unique<Enemies2>(&enemyTexture2, sf::Vector2u(3, 8), (j * 64), (i * 64)));
				}
			}

		}
	
}
void Gra::Licznik()
{

	/*
	licznik.setCharacterSize(35);
	licznik.setFillColor(sf::Color::Red);
	licznik.setFont(font);
	licznik.setString(Zegar.str());
	licznik.setPosition(view->getCenter().x - 512, view->getCenter().y - 180);
	*/

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

	Score.setCharacterSize(35);
	Score.setFillColor(sf::Color::Red);
	Score.setFont(font);
	Score.setString(ssScore.str());
	Score.setPosition(view->getCenter().x - 512, view->getCenter().y - 280);

	Oceny.setCharacterSize(35);
	Oceny.setFont(font);
	Oceny.setString(ssOceny.str());
	Oceny.setPosition(view->getCenter().x - 540, view->getCenter().y - 320);

	window->draw(Oceny);
	window->draw(Score);
	window->draw(licznik);


}
void Gra::PlayerCollision(sf::Vector2f& direction)
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


				if (intersectX > intersectY)
				{
					if (deltax > 0.0f)
					{
						
						this->player->body.move(-intersectX * 1.0f, 0.0f);

						direction.x = 1.0f;
						direction.y = 0.0f;
					}
					else
					{
						
						this->player->body.move(intersectX * 1.0f, 0.0f);

						direction.x = -1.0f;
						direction.y = 0.0f;
					}
				}
				else
				{
					if (deltay > 0.0f)
					{
						
						this->player->body.move(0.0f, -intersectY * 1.0f);

						direction.x = 0.0f;
						direction.y = 1.0f;
					}
					else
					{
						
						this->player->body.move(0.0f, intersectY * 1.0f);

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
void Gra::PlayerCollisionST(sf::Vector2f& direction)
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
			sf::Vector2f thishalfsize(this->ST_level->MatrixST[i][j].getGlobalBounds().width / 2.0f, (ST_level->MatrixST[i][j].getGlobalBounds().height - 11) / 2.0f);
			sf::Vector2f otherhalfsize = this->player->body.getSize() / 2.0f;

			bool t;

			deltax = otherposition.x - thisposition.x;
			deltay = otherposition.y - thisposition.y;

			intersectX = std::abs(deltax) - (otherhalfsize.x + thishalfsize.x);
			intersectY = std::abs(deltay) - (otherhalfsize.y + thishalfsize.y);

			if (intersectX < 0.0f && intersectY < 0.0f)
			{
				

				if (intersectX > intersectY)
				{
					if (deltax > 0.0f)
					{
						this->ST_level->MatrixST[i][j].move(0.0f, 0.0f);
						this->player->body.move(-intersectX * 1.0f, 0.0f);

						direction.x = 1.0f;
						direction.y = 0.0f;
					}
					else
					{
						this->ST_level->MatrixST[i][j].move(0.0f, 0.0f);
						this->player->body.move(intersectX * 1.0f, 0.0f);

						direction.x = -1.0f;
						direction.y = 0.0f;
					}
				}
				else
				{
					if (deltay > 0.0f)
					{
						this->ST_level->MatrixST[i][j].move(0.0f, 0.0f);
						this->player->body.move(0.0f, -intersectY * 1.0f);

						direction.x = 0.0f;
						direction.y = 1.0f;
					}
					else
					{
						this->ST_level->MatrixST[i][j].move(0.0f, 0.0f);
						this->player->body.move(0.0f, intersectY * 1.0f);

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
void Gra::WrogowieCollisionST(sf::Vector2f& direction)
{

	float deltax;
	float deltay;
	float intersectX;
	float intersectY;
	for (size_t x = 0; x < przeciwnik.size(); x++)
	{

		for (size_t i = 0; i < this->ST_level->MatrixST.size(); i++)
		{
			for (size_t j = 0; j < this->ST_level->MatrixST[i].size(); j++)
			{
				sf::Vector2f thisposition = this->ST_level->MatrixST[i][j].getPosition();
				sf::Vector2f otherposition = this->przeciwnik[x]->GetPosition();
				sf::Vector2f thishalfsize(this->ST_level->MatrixST[i][j].getGlobalBounds().width / 2.0f, (ST_level->MatrixST[i][j].getGlobalBounds().height - 11) / 2.0f);
				sf::Vector2f otherhalfsize = this->przeciwnik[x]->body.getSize() / 2.0f;

				bool t;

				deltax = otherposition.x - thisposition.x;
				deltay = otherposition.y - thisposition.y;

				intersectX = std::abs(deltax) - (otherhalfsize.x + thishalfsize.x);
				intersectY = std::abs(deltay) - (otherhalfsize.y + thishalfsize.y);

				if (intersectX < 0.0f && intersectY < 0.0f)
				{
					

					if (intersectX > intersectY)
					{
						if (deltax > 0.0f)
						{
							
							this->przeciwnik[x]->body.move(-intersectX * 1.0f, 0.0f);
							przeciwnik[x]->odbicieP();
							direction.x = 1.0f;
							direction.y = 0.0f;
						}
						else
						{
							
							this->przeciwnik[x]->body.move(intersectX * 1.0f, 0.0f);
							przeciwnik[x]->odbicieL();
							direction.x = -1.0f;
							direction.y = 0.0f;
						}
					}
					else
					{
						if (deltay > 0.0f)
						{
							
							this->przeciwnik[x]->body.move(0.0f, -intersectY * 1.0f);

							direction.x = 0.0f;
							direction.y = 1.0f;
						}
						else
						{
							
							this->przeciwnik[x]->body.move(0.0f, intersectY * 1.0f);

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
					this->przeciwnik[x]->OnCollision(direction);
				}
			}

		}
	}
}
void Gra::CombatCollision2(sf::Vector2f& direction)
{
	float deltax;
	float deltay;
	float intersectX;
	float intersectY;

	for (size_t x = 0; x < przeciwnik.size(); x++)
	{
	sf::Vector2f thisposition = this->przeciwnik[x]->GetPosition();
	sf::Vector2f otherposition = this->player->GetPosition();
	sf::Vector2f thishalfsize = this->przeciwnik[x]->body.getSize() / 2.0f;
	sf::Vector2f otherhalfsize = this->player->body.getSize() / 2.0f;

	bool t;

	deltax = otherposition.x - thisposition.x;
	deltay = otherposition.y - thisposition.y;

	intersectX = std::abs(deltax) - (otherhalfsize.x + thishalfsize.x);
	intersectY = std::abs(deltay) - (otherhalfsize.y + thishalfsize.y);

	if (intersectX < 0.0f && intersectY < 0.0f)
	{
		

		if (intersectX > intersectY)
		{
			if (deltax > 0.0f)
			{
				player->body.setPosition(256, 1427);
				damage.play();
				zycie--;
				ssOceny.str("");
				wysZycie();
			}
			else
			{
				player->body.setPosition(256, 1427);
				damage.play();
				zycie--;
				ssOceny.str("");
				wysZycie();
			}
		}
		else
		{
			if (deltay < 0.0f)
			{
				przeciwnik.erase(przeciwnik.begin() + x);
				damage.play();
				zycie += 0.25;
				ssOceny.str("");
				wysZycie();
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
void Gra::WrogowieCollision(sf::Vector2f& direction)
{

	float deltax;
	float deltay;
	float intersectX;
	float intersectY;

	for (size_t x = 0; x < przeciwnik.size(); x++)
	{

		for (size_t i = 0; i < this->level->Matrix.size(); i++)
		{
			for (size_t j = 0; j < this->level->Matrix[i].size(); j++)
			{
				sf::Vector2f thisposition = this->level->Matrix[i][j].getPosition();
				sf::Vector2f otherposition = this->przeciwnik[x]->GetPosition();
				sf::Vector2f thishalfsize(this->level->Matrix[i][j].getGlobalBounds().width / 2.0f, (level->Matrix[i][j].getGlobalBounds().height) / 2.0f);
				sf::Vector2f otherhalfsize = this->przeciwnik[x]->body.getSize() / 2.0f;

				bool t;

				deltax = otherposition.x - thisposition.x;
				deltay = otherposition.y - thisposition.y;

				intersectX = std::abs(deltax) - (otherhalfsize.x + thishalfsize.x);
				intersectY = std::abs(deltay) - (otherhalfsize.y + thishalfsize.y);

				if (intersectX < 0.0f && intersectY < 0.0f)
				{
					

					if (intersectX > intersectY)
					{
						if (deltax > 0.0f)
						{
							
							this->przeciwnik[x]->body.move(-intersectX * 1.0f, 0.0f);
							przeciwnik[x]->odbicieP();
							direction.x = 1.0f;
							direction.y = 0.0f;
						}
						else
						{
							
							this->przeciwnik[x]->body.move(intersectX * 1.0f, 0.0f);
							przeciwnik[x]->odbicieL();
							direction.x = -1.0f;
							direction.y = 0.0f;
						}
					}
					else
					{
						if (deltay > 0.0f)
						{
							
							this->przeciwnik[x]->body.move(0.0f, -intersectY * 1.0f);

							direction.x = 0.0f;
							direction.y = 1.0f;
						}
						else
						{
							
							this->przeciwnik[x]->body.move(0.0f, intersectY * 1.0f);

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
					this->przeciwnik[x]->OnCollision(direction);
				}
			}

		}
	}

}
void Gra::enemyWall(sf::Vector2f& direction)
{

	float deltax;
	float deltay;
	float intersectX;
	float intersectY;

	for (size_t x = 0; x < przeciwnik.size(); x++)
	{

		for (size_t i = 0; i < this->levelE->MatrixE.size(); i++)
		{
			for (size_t j = 0; j < this->levelE->MatrixE[i].size(); j++)
			{
				sf::Vector2f thisposition = this->levelE->MatrixE[i][j].getPosition();
				sf::Vector2f otherposition = this->przeciwnik[x]->GetPosition();
				sf::Vector2f thishalfsize(this->levelE->MatrixE[i][j].getGlobalBounds().width / 2.0f, (level->Matrix[i][j].getGlobalBounds().height) / 2.0f);
				sf::Vector2f otherhalfsize = this->przeciwnik[x]->body.getSize() / 2.0f;

				bool t;

				deltax = otherposition.x - thisposition.x;
				deltay = otherposition.y - thisposition.y;

				intersectX = std::abs(deltax) - (otherhalfsize.x + thishalfsize.x);
				intersectY = std::abs(deltay) - (otherhalfsize.y + thishalfsize.y);

				if (intersectX < 0.0f && intersectY < 0.0f)
				{
					

					if (intersectX > intersectY)
					{
						if (deltax > 0.0f)
						{
							
							this->przeciwnik[x]->body.move(-intersectX * 1.0f, 0.0f);
							przeciwnik[x]->odbicieP();
							direction.x = 1.0f;
							direction.y = 0.0f;
						}
						else
						{
							
							this->przeciwnik[x]->body.move(intersectX * 1.0f, 0.0f);
							przeciwnik[x]->odbicieL();
							direction.x = -1.0f;
							direction.y = 0.0f;
						}
					}
					else
					{
						if (deltay > 0.0f)
						{
							
							this->przeciwnik[x]->body.move(0.0f, -intersectY * 1.0f);

							direction.x = 0.0f;
							direction.y = 1.0f;
						}
						else
						{
							
							this->przeciwnik[x]->body.move(0.0f, intersectY * 1.0f);

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
					this->przeciwnik[x]->OnCollision(direction);
				}
			}

		}
	}

}
void Gra::CoinCollision(sf::Vector2f& direction)
{

	for (size_t x = 0; x < coin.size(); x++)
	{

		if (player->body.getGlobalBounds().intersects(coin[x]->ects.getGlobalBounds()))
		{
			coin.erase(coin.begin() + x);
			score++;
			ssScore.str("");
			ssScore << "Punkty ECTS: " << score;
			Score.setString(ssScore.str());

			sound1.play();
			if (score == wygryw)
			{
				window->close();
				wygrana();
			}


		}
	}
	
}
