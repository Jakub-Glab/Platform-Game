#include "Menu.h"

Menu::Menu(float width, float height)
{
	if (!font1.loadFromFile("Fonts/font.ttf"))
	{
		std::cout << "Blad z zaladowaniem czcionki!!!" << std::endl;
		
	}
	menu[0].setFont(font1);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Play");
	menu[0].setPosition(sf::Vector2f((width / 2)-50, height / (LICZBA_OPCJI + 1) * 1));

	menu[1].setFont(font1);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Sterowanie");
	menu[1].setPosition(sf::Vector2f((width / 2)-115, height / (LICZBA_OPCJI + 1) * 2));

	menu[2].setFont(font1);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Exit");
	menu[2].setPosition(sf::Vector2f((width / 2)-50, height / (LICZBA_OPCJI + 1) * 3));

	selectedItemIndex = 0;
}


Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < LICZBA_OPCJI; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < LICZBA_OPCJI)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}