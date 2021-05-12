#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

#define LICZBA_OPCJI 3

class Menu
{
public:
	Menu(float width, float height);
	~Menu();

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; }

private:
	int selectedItemIndex;
	sf::Font font1;
	sf::Text menu[LICZBA_OPCJI];

};