#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
class Sterowanie
{
public:
	sf::RenderWindow* window;
	sf::Texture tlo;
	sf::Event evnt;
	sf::Sprite Sprite;
	Sterowanie();
	~Sterowanie();
	bool Run();
	void Update();
	void Render();
	void loadTextures();
	void loadData();
};

