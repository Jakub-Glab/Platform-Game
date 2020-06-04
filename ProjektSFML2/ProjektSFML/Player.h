#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Kolizje.h"
#include "ECTS.h"

class Player
{
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight);
	~Player();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void OnCollision(sf::Vector2f direction);

	sf::Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }
	bool isCollidingWithCoin(Coin* coin) {
		if (body.getGlobalBounds().intersects(coin->getGlobalBounds())) {
			return true;
		}
		return false;
	}
	sf::RectangleShape body;
private:
	
	Animation animation;
	unsigned int row;
	float speed;
	bool faceRight;

	sf::Vector2f velocity;
	bool canJump;
	float jumpHeight;
};

