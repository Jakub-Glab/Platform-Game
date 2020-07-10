#pragma once
#include <SFML/Graphics.hpp>
#include "Animacje.h"
#include "Kolizje.h"
#include "ECTS.h"


class Enemies2 
{
public:
	Enemies2(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight);
	~Enemies2();
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
	sf::Vector2f velocity;
	void odbicieL();
	void odbicieP();
private:
	
	
	
	Animation animation;
	unsigned int row;
	bool upkey;
	float speed;
	float jumpHeight;
	bool faceRight;
};
