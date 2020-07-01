#pragma once
#include <SFML/Graphics.hpp>
#include "Animacje.h"
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
	void DoubleJump();
	sf::Event event;
	sf::Clock upkeytimer;
	
	sf::Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }
	sf::FloatRect getGlobalBounds() {
		return body.getGlobalBounds();
	}
	sf::RectangleShape body;
	bool canJump;
private:
	
	Animation animation;
	unsigned int row;
	float speed;
	bool upkey;
	bool faceRight;
	sf::Vector2f velocity;
	
	float jumpHeight;
};

