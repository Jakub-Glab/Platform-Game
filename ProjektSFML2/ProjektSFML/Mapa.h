#pragma once
#include <vector>
#include <map>
#include <SFML\Graphics\Sprite.hpp>

class Level
{
public:
	Level();
	Level(std::map<char, sf::Texture*> groundTextures);
	~Level();

	std::vector<std::vector<sf::Sprite>> Matrix;
	std::vector<std::vector<char>> Arrangement;

	void loadMap();
	void createMap(std::map<char, sf::Texture*> groundTextures);
};