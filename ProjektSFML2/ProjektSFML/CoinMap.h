#pragma once
#include <vector>
#include "Animacje.h"
#include <map>
#include <SFML\Graphics\Sprite.hpp>
#include "Kolizje.h"
#include "Animacje.h"
/*
class Coin :public sf::Sprite
{
public:
	Coin(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f newPos);
	~Coin();
	void Update(float deltaTime);
	std::vector<std::vector<sf::Sprite>> MatrixCoin;
	std::vector<std::vector<char>> PozycjaCoin;
	void loadCoin();
	void createCoin();
	sf::RectangleShape ects;
private:
	sf::Texture tekstura;
	void AddTexture(const std::string& filename) { tekstura.loadFromFile(filename); this->setTexture(tekstura); };
	Animation animation;
	bool faceRight;
	unsigned int row;
};
*/
class Coin
{
public:
	Coin();
	Coin(std::map<char, sf::Texture*> CoinTextures);
	~Coin();

	std::vector<std::vector<sf::Sprite>> MatrixCoin;
	std::vector<std::vector<char>> PozycjaCoin;

	void loadCoin();
	void createCoin(std::map<char, sf::Texture*> CoinTextures);

};