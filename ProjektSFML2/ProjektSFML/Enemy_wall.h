#pragma once
#include <vector>
#include <map>
#include <SFML\Graphics\Sprite.hpp>
class LevelE
{
public:
	LevelE();
	LevelE(std::map<char, sf::Texture*> groundTexturesE);
	~LevelE();

	std::vector<std::vector<sf::Sprite>> MatrixE;
	std::vector<std::vector<char>> ArrangementE;

	void loadMapE();
	void createMapE(std::map<char, sf::Texture*> groundTexturesE);
};

