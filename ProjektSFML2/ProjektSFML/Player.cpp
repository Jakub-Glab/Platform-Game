#include "Player.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight) : 
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	this->jumpHeight = jumpHeight;
	row = 0;
	faceRight = true;

	body.setSize(sf::Vector2f(64.0f, 64.0f));
	//body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(603.774f, 240.0f);
	body.setTexture(texture);
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{

	velocity.x = 0.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		velocity.x -= speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		velocity.x += speed;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && canJump)
	{
		canJump = false;
		velocity.y = -sqrtf(1.3f * 981.0f * jumpHeight);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump)
	{
		canJump = false;
		velocity.y = -sqrtf(1.3f * 981.0f * jumpHeight);
	}
	

	velocity.y += 981.0f * deltaTime; // <----------- Nasza grawitacja

	if (velocity.x == 0.0f)
	{
		row = 0;
	}
	
	else if ( canJump == true)
	{
		row = 2;
		if (velocity.x > 0.0f)
		{
			faceRight = true;
		}
		else
		{
			faceRight = false;
		}
	}
	else
	{
		row = 1;

		if (velocity.x > 0.0f)
			faceRight = true;
		else
			faceRight = false;
	}

	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);

}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Player::OnCollision(sf::Vector2f direction)
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
		canJump = true;
	}
	else if (direction.y > 0.0f)
	{
		//Kolizja od góry
		velocity.y = 0.0f;
	}
}
