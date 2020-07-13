#include "Wrogowie.h"



Enemies2::Enemies2(sf::Texture* texture1, sf::Vector2u imagecount, float posX, float posY):
	animation(texture1, imagecount)
{
	
	this->speed = speed;
	this->jumpHeight = jumpHeight;
	animation.switchTime = switchTime;
	row = 0;
	faceRight = true;
	upkey = false;
	body.setSize(sf::Vector2f(64.0f, 64.0f));
	body.setPosition(posX, posY);
	body.setTexture(texture1);
	
	
}

Enemies2::~Enemies2()
{
}

void Enemies2::Update(float deltaTime)
{

	//velocity.y += 981.0f * deltaTime;
	velocity.y = 0;
	velocity.x = speed;
	if (velocity.x == 0.0f)
	{
		row = 0;
	}

	else
	{
		row = 2;

		if (velocity.x > 0.0f)
			faceRight = true;
		else
			faceRight = false;
	}

	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);

}

void Enemies2::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Enemies2::OnCollision(sf::Vector2f direction)
{
	if (direction.x < 0.0f)
	{
		//Kolizja z lewej
		velocity.x = 0.0f;
	}
	else if (direction.x > 0.0f)
	{
		//Kolizja z prawej
		velocity.x = 0.0f;
	}
	if (direction.y < 0.0f)
	{
		//Kolizja od do³u
		velocity.y = 0.0f;
	}
	else if (direction.y > 0.0f)
	{
		//Kolizja od góry
		velocity.y = 0.0f;
	}
}
void Enemies2::odbicieL()
{
	speed = -100.f;
}
void Enemies2::odbicieP()
{
	speed = 100.f;
}
