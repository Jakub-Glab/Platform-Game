#pragma once
#include <SFML/Graphics.hpp>
#include "Animacje2.h"



class Enemies2 
{
public:
	Enemies2(sf::Texture* texture1, sf::Vector2u imagecount, float posX, float posY);
	~Enemies2();
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void OnCollision(sf::Vector2f direction);
	float switchTime = 0.075f;
	float speed = 200.0f;
	sf::Event event;
	sf::Clock upkeytimer;
	sf::Vector2f GetPosition() { return body.getPosition(); }
	sf::RectangleShape body;
	sf::Vector2f velocity;
	bool canJump;
	void odbicieL();
	void odbicieP();
private:
	
	Animation2 animation;
	unsigned int row;
	bool upkey;
	float jumpHeight;
	bool faceRight;
};
