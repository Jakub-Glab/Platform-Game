#pragma once
#include <vector>
#include <map>
#include <SFML\Graphics\Sprite.hpp>
#include "Kolizje.h"

class Items
{
public:
	Items();
	Items(std::map<char, sf::Texture*> ItemsTextures);
	~Items();

	std::vector<std::vector<sf::Sprite>> MatrixItems;
	std::vector<std::vector<char>> ArrangementItems;

	void loadItems();
	void createItems(std::map<char, sf::Texture*> ItemsTextures);
};