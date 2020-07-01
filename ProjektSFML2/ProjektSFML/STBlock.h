#pragma once
#include <vector>
#include <map>
#include <SFML\Graphics\Sprite.hpp>
	class STLevel
	{
	public:
		STLevel();
		STLevel(std::map<char, sf::Texture*> ST_textures);
		~STLevel();

		std::vector<std::vector<sf::Sprite>> MatrixST;
		std::vector<std::vector<char>> STArrangement;

		void loadMapST();
		void createMapST(std::map<char, sf::Texture*> ST_textures);
	};


