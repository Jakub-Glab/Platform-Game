#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include "Player.h"
#include "Kolizje.h"
#include "ECTS.h"
#include "Mapa.h"




int main()
{ 
	sf::Clock clock2;
	clock2.restart();
	
	
	sf::RenderWindow window(sf::VideoMode(1024, 640), "POLIBUDA", sf::Style::Close | sf::Style::Resize);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1024, 640));

	sf::Texture tlo;
	tlo.loadFromFile("tlo3.jpg");
	sf::Sprite Tlo;
	Tlo.setTexture(tlo);

	sf::Texture playerTexture;
	playerTexture.loadFromFile("spritesheet3.png");
	Player player(&playerTexture, sf::Vector2u(3, 8), 0.1f, 200.0f, 320.0f);

	std::map<char, sf::Texture*> GroundTextures;
	sf::Texture* one = new sf::Texture;
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
	
	Level level(GroundTextures);

	sf::Font font;
	sf::Time elapsed1 = clock2.getElapsedTime();
	sf::Text licznik;
	std::ostringstream Zegar;
	licznik.setCharacterSize(35);
	licznik.setFillColor(sf::Color::Red);
	licznik.setFont(font);
	Zegar << "Czas: " << elapsed1.asSeconds();
	licznik.setString(Zegar.str());
	
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
	

	int score = 0;
	font.loadFromFile("font.ttf");
	std::ostringstream ssScore;
	ssScore << "Punkty ECTS: " << "["<<score<<"]";
	sf::Text lblScore;
	lblScore.setCharacterSize(45);
	lblScore.setFillColor(sf::Color::Red);
	lblScore.setFont(font);
	lblScore.setString(ssScore.str());

	float deltaTime = 0.0f;
	sf::Clock clock;
	
	
	
	

	while (window.isOpen()) {

		

		deltaTime = clock.restart().asSeconds();
		if (deltaTime > 1.0f / 20.0f)
			deltaTime = 1.0f / 20.0f;
		Tlo.setPosition(view.getCenter().x-512, view.getCenter().y-320);
		lblScore.setPosition(view.getCenter().x-512, view.getCenter().y-280);
		licznik.setPosition(view.getCenter().x - 512, view.getCenter().y - 180);
		sf::Event evnt;
		while (window.pollEvent(evnt)) {

			switch (evnt.type) {

			case sf::Event::Closed:
				window.close();
				break;

			}
		}
		player.Update(deltaTime);
		window.setFramerateLimit(30);
		Collider col = player.GetCollider();
		sf::Vector2f direction;
		sf::Vector2f direction2;
		
		for (int i = 0; i < coinVec.size(); i++) {
			if (player.isCollidingWithCoin(coinVec[i])) {
				coinVec[i]->setPos({ 422234, 423432 });
				score++;
				ssScore.str("");
				ssScore << "Punkty ECTS: " << "[" << score << "]";
				lblScore.setString(ssScore.str());
			}
		}
		view.setCenter(player.GetPosition());
		window.clear();
		window.draw(Tlo);
		window.setView(view);
		player.Draw(window);
		
		for (int i = 0; i < level.Matrix.size(); i++)
		{
			for (int j = 0; j < level.Matrix[i].size(); j++)
			{
				window.draw(level.Matrix[i][j]);
			}
		}
		float deltax; //zmienna odleglosc miedzy pozycja x bohatera i pozycja x innych obiektow
		float deltay; //zmienna odleglosc miedzy pozycja y bohatera i pozycja y innych obiektow
		float intersectX; //przeciecie w osi X obiektu z bohaterem
		float intersectY; //przeciecie w osi Y obiektu z bohaterem

		//sprawdzamy kolizje naszego bohatera z kazdym obiektem na naszej mapie
		for (size_t i = 0; i < level.Matrix.size(); i++)
		{
			for (size_t j = 0; j < level.Matrix[i].size(); j++)
			{


				sf::Vector2f thisposition = level.Matrix[i][j].getPosition(); //pozycja bohatera
				sf::Vector2f otherposition = player.GetPosition(); //pozycja aktualnego obiektu
				sf::Vector2f thishalfsize(level.Matrix[i][j].getGlobalBounds().width / 2.0f, level.Matrix[i][j].getGlobalBounds().height / 2.0f);
				sf::Vector2f otherhalfsize(player.body.getGlobalBounds().width / 2.0f, player.body.getGlobalBounds().height / 2.0f);
				bool t;

				deltax = otherposition.x - thisposition.x;
				deltay = otherposition.y - thisposition.y;

				intersectX = std::abs(deltax) - (otherhalfsize.x + thishalfsize.x);
				intersectY = std::abs(deltay) - (otherhalfsize.y + thishalfsize.y);

				if (intersectX < 0.0f && intersectY < 0.0f) //jesli obie osie przeciecia obiektu sa mniejsze od 0 to znaczy ze obiekty na siebie nachodza i nastepuje zderzenie
				{
					float p = 1.0f;

					if (intersectX > intersectY)
					{
						if (deltax > 0.0f)
						{
							level.Matrix[i][j].move(intersectX * (1.0f - p), 0.0f); //odbicia podczas zderzen kazdy w innym kierunku
							player.body.move(-intersectX * p, 0.0f);

							direction.x = 1.0f;
							direction.y = 0.0f;
						}
						else
						{
							level.Matrix[i][j].move(-intersectX * (1.0f - p), 0.0f);
							player.body.move(intersectX * p, 0.0f);

							direction.x = -1.0f;
							direction.y = 0.0f;
						}
					}
					else
					{
						if (deltay > 0.0f)
						{
							level.Matrix[i][j].move(0.0f, intersectY * (1.0f - p));
							player.body.move(0.0f, -intersectY * p);

							direction.x = 0.0f;
							direction.y = 1.0f;
						}
						else
						{
							level.Matrix[i][j].move(0.0f, -intersectY * (1.0f - p));
							player.body.move(0.0f, intersectY * p);

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
					player.OnCollision(direction);
				}
			}

		}

		coin1.drawTo(window);
		coin2.drawTo(window);
		coin3.drawTo(window);
		coin4.drawTo(window);
		window.draw(lblScore);
		window.draw(licznik);
		window.display();
	}

	return 0;
}