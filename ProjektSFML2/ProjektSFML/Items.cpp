#include <iostream>
#include <fstream>
#include <string>
#include "Items.h"

Items::Items()
{
}

Items::Items(std::map<char, sf::Texture*> ItemsTextures)
{
	loadItems();
	createItems(ItemsTextures);
}

Items::~Items()
{
}

void Items::loadItems()
{
	std::ifstream file("items.txt");
	std::string charLine;
	std::vector<char> textureLine;
	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, charLine);
			for (int i = 0; i < charLine.length(); i++)
			{
				textureLine.push_back(charLine[i]);
			}
			ArrangementItems.push_back(textureLine);
			textureLine.clear();
			charLine.clear();
		}
	}
}

void Items::createItems(std::map<char, sf::Texture*> ItemsTextures)
{
	std::vector<sf::Sprite> spritesLine;
	sf::Sprite chunk;


	for (int i = 0; i < ArrangementItems.size(); i++)
	{
		for (int j = 0; j < ArrangementItems[i].size(); j++)
		{
			if (ArrangementItems[i][j] != '0')
			{
				
				chunk.setTexture(*ItemsTextures[ArrangementItems[i][j]]);
				chunk.setScale(1.66f, 1.66f);
				chunk.setPosition(float(j * 128), float(i * 128));
				spritesLine.push_back(chunk);
			}
		}
		MatrixItems.push_back(spritesLine);
		spritesLine.clear();
	}
}