#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include "Player.h"
//#include "ECTS.h"
#include "Mapa.h"
#include "Chmurki.h"
#include "STBlock.h"
#include <conio.h>
#include <Windows.h>
#include "Wrogowie.h"
#include <fstream>
#include <cstdio>
#include <ctime>
#include "Animacje2.h"
#include "Enemy_wall.h"
#include "Coiny.h"


class Gra
{
public:
	//Gracz:
	Player* player;
	//Coiny:
	//Coin* coin;
	sf::RenderWindow* window;
	sf::Image icon;
	sf::View* view;
	Level* level;
	LevelE* levelE;
	STLevel* ST_level;
	sf::Event evnt;
	sf::Clock clock;
	sf::Clock clock2;
	std::map<char, sf::Texture*> GroundTextures;
	//std::map<char, sf::Texture*> CoinTextures;
	std::map<char, sf::Texture*> ST_textures;
	std::map<char, sf::Texture*> GroundTexturesE;
	float VIEW_HEIGHT = 640.0f;
	sf::Vector2f direction;
	sf::Vector2f direction2;
	sf::Vector2f direction3;
	float deltaTime = 0.0f;
	//Tekstury:
	sf::Texture playerTexture;
	sf::Texture enemyTexture2;
	sf::Texture coinTexture;
	// old coin:  sf::Texture coinTexture;
	sf::Texture tlo;
	sf::Sprite Tlo;
	//Bloki:
	sf::Texture* grass = new sf::Texture;
	sf::Texture* water = new sf::Texture;
	sf::Texture* wall = new sf::Texture;
	sf::Texture* box = new sf::Texture;
	sf::Texture* stone = new sf::Texture;
	sf::Texture* e_wall = new sf::Texture;
	//Wektor coinów:
	//Rzeczy do licznika punktów:
	std::ostringstream ssScore;
	std::ostringstream ssOceny;
	
	
	sf::Text Score;
	sf::Font font;
	sf::Time elapsed1 = clock2.getElapsedTime();
	sf::Text licznik;
	std::ostringstream Zegar;
	int score = 0;
	float c = 0.0f;
	//DŸwiêki:
	sf::SoundBuffer coinsound;
	sf::SoundBuffer jumpSound1;
	sf::SoundBuffer jumpSound2;
	sf::SoundBuffer damageSound;
	sf::Sound sound1;
	sf::Sound damage;
	sf::Sound jump_sound1;
	sf::Sound jump_sound2;
	std::vector<std::unique_ptr<RuchomySprite>> alien;
	std::vector<std::unique_ptr<Enemies2>> przeciwnik;
	std::vector<std::unique_ptr<Coiny>> coin;
	sf::Clock clock3;
	sf::Time elapsed3;
	sf::Text Oceny;
	std::vector<std::vector<char>> EnemiesLocation;
	std::vector<std::vector<char>> CoinLocation;
	sf::Color orange;
	std::clock_t start;
	double duration;
	float zycie = 4;
	int wygryw;



	

	Gra(int win);
	~Gra();
	
	void wysPunkty();
	void wysZycie();
	void loadTextures();
	void loadData();
	void Chmurki();
	void TworzCoin();
	void wygrana();
	void przegrana();
	void Czas();
	bool Run();
	void Update();
	void Render();
	void Licznik();
	void EnemiesLoad();
	void PlayerCollision(sf::Vector2f& direction);
	
	void PlayerCollisionST(sf::Vector2f& direction);
	
	void CombatCollision2(sf::Vector2f& direction);
	
	void CoinCollision(sf::Vector2f& direction);
	void WrogowieCollision(sf::Vector2f& direction);
	void WrogowieCollisionST(sf::Vector2f& direction);
	void enemyWall(sf::Vector2f& direction);


};

	


