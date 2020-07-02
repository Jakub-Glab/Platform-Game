#include "STBlock.h"
#include <iostream>
#include <fstream>
#include <string>


STLevel::STLevel(std::map<char, sf::Texture*> ST_textures)
{
	loadMapST();
	createMapST(ST_textures);
}

STLevel::~STLevel()
{
}

void STLevel::loadMapST()
{
	std::ifstream file("Maps/mapaST.txt");
	std::string charLine;
	std::vector<char> mapLine;
	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, charLine);
			for (int i = 0; i < charLine.length(); i++)
			{
				mapLine.push_back(charLine[i]);
			}
			STArrangement.push_back(mapLine);
			mapLine.clear();
			charLine.clear();
		}
	}
}

void STLevel::createMapST(std::map<char, sf::Texture*> ST_textures)
{
	std::vector<sf::Sprite> spritesLine;
	sf::Sprite chunk;

	for (int i = 0; i < STArrangement.size(); i++)
	{
		for (int j = 0; j < STArrangement[i].size(); j++)
		{

			if (STArrangement[i][j] != '0')
			{
				chunk.setTexture(*ST_textures[STArrangement[i][j]]);
				chunk.setScale(1.0f, 1.0f);
				chunk.setPosition(float(j * 64), float(i * 64));
				spritesLine.push_back(chunk);
			}

		}
		MatrixST.push_back(spritesLine);
		spritesLine.clear();
	}
}
