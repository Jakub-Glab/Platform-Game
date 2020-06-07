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
	sf::RenderWindow* window;
	sf::View* view;
	Level* level;
	sf::Event evnt;
	sf::Clock clock;
	sf::Clock clock2;
	Coin* coin;
	std::map<char, sf::Texture*> GroundTextures;
	float VIEW_HEIGHT = 640.0f;
	sf::Vector2f direction;
	float deltaTime = 0.0f;
	sf::Texture playerTexture;
	Collider col = player->GetCollider();
	sf::Texture tlo;
	sf::Sprite Tlo;
	sf::Texture* one = new sf::Texture;

	Game();
	~Game();
	void loadTextures();
	void loadData();
	bool Run();
	void Update();
	void Render();
	void CheckCollision(sf::Vector2f& direction, float p);

};

