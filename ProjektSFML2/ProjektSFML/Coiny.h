#pragma once
#include "Animacje2.h"
class Coiny
{
public:
	Coiny(sf::Texture* texture, sf::Vector2u imageCount, float posX, float posY);
	~Coiny();
	float switchTime = 0.1f;
	void Draw(sf::RenderWindow& window);
	void Update(float deltaTime);
	sf::RectangleShape ects;
private:
	Animation2 animation;
	bool faceRight;
	unsigned int row;
};

