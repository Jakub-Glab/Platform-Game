#pragma once
#include <SFML/Graphics.hpp>
#include "Animacje2.h"



class Player
{
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount);
	~Player();
	float switchTime = 0.1f;
	float speed = 210.0f;
	float jumpHeight = 320.0f;
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void OnCollision(sf::Vector2f direction);
	void DoubleJump();
	sf::Event event;
	sf::Clock upkeytimer;
	
	sf::Vector2f GetPosition() { return body.getPosition(); }

	sf::RectangleShape body;
	bool canJump;
private:
	
	Animation2 animation;
	unsigned int row;
	bool upkey;
	bool faceRight;
	sf::Vector2f velocity;
	
};

