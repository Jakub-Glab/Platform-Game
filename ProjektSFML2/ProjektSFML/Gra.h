#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include "Player.h"
#include "Enemies.h"
#include "Kolizje.h"
//#include "ECTS.h"
#include "Mapa.h"
#include "Chmurki.h"
#include "CoinMap.h"
#include "STBlock.h"
#include <conio.h>
#include <Windows.h>
#include "Wrogowie.h"
#include <fstream>


class Gra
{
public:
	//Gracz:
	Player* player;
	//Coiny:
	Enemies* wrog;
	Coin* coin;
	sf::RenderWindow* window;
	sf::Image icon;
	sf::View* view;
	Level* level;
	STLevel* ST_level;
	sf::Event evnt;
	sf::Clock clock;
	sf::Clock clock2;
	std::map<char, sf::Texture*> GroundTextures;
	std::map<char, sf::Texture*> CoinTextures;
	std::map<char, sf::Texture*> ST_textures;
	float VIEW_HEIGHT = 640.0f;
	sf::Vector2f direction;
	sf::Vector2f direction2;
	sf::Vector2f direction3;
	float deltaTime = 0.0f;
	//Tekstury:
	sf::Texture playerTexture;
	sf::Texture enemyTexture;
	sf::Texture enemyTexture2;
	// old coin:  sf::Texture coinTexture;
	Collider col = player->GetCollider();
	sf::Texture tlo;
	sf::Sprite Tlo;
	//Bloki:
	sf::Texture* grass = new sf::Texture;
	sf::Texture* water = new sf::Texture;
	sf::Texture* wall = new sf::Texture;
	sf::Texture* box = new sf::Texture;
	sf::Texture* stone = new sf::Texture;
	sf::Texture* coinT = new sf::Texture;
	//Wektor coin�w:
	std::vector<Coin*> coinVec;
	//Rzeczy do licznika punkt�w:
	std::ostringstream ssScore;
	std::ostringstream ssOceny;
	
	sf::Text Score;
	sf::Font font;
	sf::Time elapsed1 = clock2.getElapsedTime();
	sf::Text licznik;
	std::ostringstream Zegar;
	int score = 0;
	float c = 0.0f;
	//D�wi�ki:
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
	sf::Clock clock3;
	sf::Time elapsed3;
	sf::Text Oceny;
	std::vector<std::vector<char>> EnemiesLocation;
	sf::Color orange;

	float zycie = 4;

	Gra();
	~Gra();
	void wysPunkty();
	void wysZycie();
	void loadTextures();
	void loadData();
	void Chmurki();
	//void TworzCoin();
	void wygrana(float& zycie);
	void przegrana();
	void Czas();
	bool Run();
	void Update();
	void Render();
	void Licznik();
	void EnemiesLoad();
	void PlayerCollision(sf::Vector2f& direction, float p);
	void EnemyCollision(sf::Vector2f& direction, float p);
	void PlayerCollisionST(sf::Vector2f& direction, float p);
	void CombatCollision(sf::Vector2f& direction, float p);
	void CombatCollision2(sf::Vector2f& direction, float p);
	void EnemyCollisionST(sf::Vector2f& direction, float p);
	void CoinCollision(sf::Vector2f& direction, float p);
	void WrogowieCollision(sf::Vector2f& direction, float p);
	void WrogowieCollisionST(sf::Vector2f& direction, float p);
	//bool isCollidingWithCoin(std::vector<Coin*> &coinVec);


};

	


