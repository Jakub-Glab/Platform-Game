#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include "Player.h"
#include "Kolizje.h"
#include "ECTS.h"
#include "Mapa.h"

class Game
{
public:
	Player* player;
	Coin* coin;
	sf::RenderWindow* window;
	sf::View* view;
	Level* level;
	sf::Event evnt;
	sf::Clock clock;
	sf::Clock clock2;
	std::map<char, sf::Texture*> GroundTextures;
	float VIEW_HEIGHT = 640.0f;
	sf::Vector2f direction;
	float deltaTime = 0.0f;
	sf::Texture playerTexture;
	sf::Texture coinTexture;
	Collider col = player->GetCollider();
	sf::Texture tlo;
	sf::Sprite Tlo;
	sf::Texture* one = new sf::Texture;
	std::vector<Coin*> coinVec;
	std::ostringstream ssScore;
	sf::Text Score;
	sf::Font font;
	sf::Time elapsed1 = clock2.getElapsedTime();
	sf::Text licznik;
	std::ostringstream Zegar;
	int score = 0;
	float c = 0;

	//Coin* coin;
	//Coin coin2;
	//Coin coin3;
	//Coin coin4;

	Game();
	~Game();
	void wysPunkty();
	void loadTextures();
	void loadData();
	void TworzCoin();
	void Czas();
	bool Run();
	void Update();
	void Render();
	void Licznik();
	void CheckCollision(sf::Vector2f& direction, float p);
	bool isCollidingWithCoin(Coin* coin); 


};

	


