#include <iostream>
#include <fstream>
#include <string>
#include "Enemy_wall.h"

LevelE::LevelE(std::map<char, sf::Texture*> groundTexturesE)
{
	loadMapE();
	createMapE(groundTexturesE);
}

LevelE::~LevelE()
{
}

void LevelE::loadMapE()
{
	std::ifstream file("Maps/enemie_wall.txt");
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
			ArrangementE.push_back(mapLine);
			mapLine.clear();
			charLine.clear();
		}
	}
}

void LevelE::createMapE(std::map<char, sf::Texture*> groundTexturesE)
{
	std::vector<sf::Sprite> spritesLine;
	sf::Sprite chunk;

	for (int i = 0; i < ArrangementE.size(); i++)
	{
		for (int j = 0; j < ArrangementE[i].size(); j++)
		{

			if (ArrangementE[i][j] == 'F')
			{
				chunk.setTexture(*groundTexturesE[ArrangementE[i][j]]);
				chunk.setScale(1.0f, 1.0f);
				chunk.setPosition(float(j * 64), float(i * 64));
				spritesLine.push_back(chunk);
			}

		}
		MatrixE.push_back(spritesLine);
		spritesLine.clear();
	}
}
