#include "Player.h"


Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight) : 
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	this->jumpHeight = jumpHeight;
	row = 0;
	faceRight = true;
	upkey = false;
	

	body.setSize(sf::Vector2f(64.0f, 64.0f));
	body.setPosition(603.774f, 240.0f);
	body.setTexture(texture);
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	upkeytimer.restart().asSeconds();
	
	velocity.x = 0.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		velocity.x -= speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		velocity.x += speed;
	/*if (event.type == sf::Event::KeyReleased) {
		if (event.key.code == sf::Keyboard::W) {
				canJump = false;
				velocity.y = -sqrtf(1.3f * 981.0f * jumpHeight);
		}
	}*/
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && canJump)
	{
		canJump = false;
		velocity.y = -sqrtf(0.65f * 981.0f * jumpHeight);
	}
	

	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump)
	{
		canJump = false;
		velocity.y = -sqrtf(1.3f * 981.0f * jumpHeight);
	}*/
	
	velocity.y += 981.0f * deltaTime; 
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		upkey = true;
		upkeytimer.restart().asSeconds();
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		upkey = false;
	}
	if (upkey == true)
	{
		for (float up = upkeytimer.getElapsedTime().asSeconds(); up < 2; up++) //Longer it's pressed longer it jumps
		{
			velocity.y = -sqrtf(981.0f * up);
		}
	}*/
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
void Player::DoubleJump()
{
	if (canJump != false) {
		velocity.y = -sqrtf(1.3f * 981.0f * jumpHeight);
		canJump = false;
	}
}
