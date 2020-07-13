#pragma once
#include <SFML/Graphics.hpp>
class Animation2
{
public:
	Animation2(sf::Texture* texture, sf::Vector2u imageCount);
	~Animation2();
	void Update(int row, float deltaTime, bool faceRight);


public:
	sf::IntRect uvRect;
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;

	float totalTime;
	float switchTime;
};

