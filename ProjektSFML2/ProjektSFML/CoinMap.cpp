#include <iostream>
#include <fstream>
#include <string>
#include "CoinMap.h"

/*
Coin::Coin(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f newPos) :
	animation(texture, imageCount, switchTime)
{
	loadCoin();
	createCoin();
	ects.setPosition(newPos);
	ects.setSize(sf::Vector2f(32.0f, 32.0f));
	faceRight = true;
	ects.setTexture(texture);
}
Coin::~Coin()
{
}
void Coin::Update(float deltaTime)
{
	row = 0;
	faceRight = true;
	animation.Update(row, deltaTime, faceRight);
	ects.setTextureRect(animation.uvRect);
}

void Coin::loadCoin()
{
	std::ifstream file("coinMap.txt");
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
			PozycjaCoin.push_back(textureLine);
			textureLine.clear();
			charLine.clear();
		}
	}
}

void Coin::createCoin()
{
	std::vector<sf::Sprite> SpriteCoin;
	sf::Texture coinTexture;
	std::vector<std::unique_ptr<Coin>> coin;
	coinTexture.loadFromFile("CoinSheet.png");

	for (int i = 0; i < PozycjaCoin.size(); i++)
	{
		for (int j = 0; j < PozycjaCoin[i].size(); j++)
		{
			if (PozycjaCoin[i][j] != '0')
			{
				
				coin.emplace_back(std::make_unique<Coin>(&coinTexture, sf::Vector2u(1, 7), 0.2f, sf::Vector2f((j * 64), (i * 64)));
				SpriteCoin.push_back(coin);
			}
		}
		MatrixCoin.push_back(SpriteCoin);
		SpriteCoin.clear();
	}
}
*/
Coin::Coin()
{
}

Coin::Coin(std::map<char, sf::Texture*> CoinTextures)
{
	loadCoin();
	createCoin(CoinTextures);
}

Coin::~Coin()
{
}

void Coin::loadCoin()
{
	std::ifstream file("coinMap.txt");
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
			PozycjaCoin.push_back(textureLine);
			textureLine.clear();
			charLine.clear();
		}
	}
}

void Coin::createCoin(std::map<char, sf::Texture*> CoinTextures)
{
	std::vector<sf::Sprite> spritesLine;
	sf::Sprite chunk;


	for (int i = 0; i < PozycjaCoin.size(); i++)
	{
		for (int j = 0; j < PozycjaCoin[i].size(); j++)
		{
			if (PozycjaCoin[i][j] == 'C')
			{
				//chunk.setRepeated(true);
				chunk.setTexture(*CoinTextures[PozycjaCoin[i][j]]);
				chunk.setScale(0.9f, 0.9f);
				chunk.setPosition(float(j * 64), float(i * 64));
				spritesLine.push_back(chunk);
			}
		}
		MatrixCoin.push_back(spritesLine);
		spritesLine.clear();
	}
}