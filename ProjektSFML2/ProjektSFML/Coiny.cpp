#include "Coiny.h"
Coiny::Coiny(sf::Texture* texture, sf::Vector2u imageCount, float posX, float posY) :
	animation(texture, imageCount)
{
	animation.switchTime = switchTime;
	faceRight = true;
	ects.setSize(sf::Vector2f(64.0f, 64.0f));
	ects.setPosition(posX, posY);
	ects.setTexture(texture);
}
Coiny::~Coiny()
{
}
void Coiny::Update(float deltaTime)
{
	row = 0;
	faceRight = true;
	animation.Update(row, deltaTime, faceRight);
	ects.setTextureRect(animation.uvRect);
}

void Coiny::Draw(sf::RenderWindow& window)
{
	window.draw(ects);
}