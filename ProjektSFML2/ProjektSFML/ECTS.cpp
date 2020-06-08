#include "ECTS.h"


Coin::Coin(sf::Texture* texture, sf::Vector2u imageCount, float switchTime) :
	animation(texture, imageCount, switchTime)
{
	coin.setSize(sf::Vector2f(64.0f, 64.0f));
	faceRight = true;
	coin.setTexture(texture);
}
Coin::~Coin()
{
}
void Coin::Update(float deltaTime)
{
	row = 0;
	faceRight = true;
	animation.Update(row, deltaTime, faceRight);
	coin.setTextureRect(animation.uvRect);
}void Coin::Draw(sf::RenderWindow& window)
{
	window.draw(coin);
}