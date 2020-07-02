#include <SFML/Graphics.hpp>
#include "Gra.h"
#include "Chmurki.h"
#include "Menu.h"
#include "Sterowanie.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "Gra MENU");
	sf::Clock clock;
	sf::Time elapsed;
	srand(time(NULL));

	Menu menu(window.getSize().x, window.getSize().y);
	sf::Texture texture;
	texture.loadFromFile("Textures/background.png");
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setPosition(0, 0);

	sf::Texture texture2;
	texture2.loadFromFile("Textures/background2.png");
	sf::Sprite sprite2;
	sprite2.setTexture(texture2);
	sprite2.setPosition(0, 0);

	sf::SoundBuffer MenuSound;
	sf::Sound menu_sound;
	if (!MenuSound.loadFromFile("Sounds/menusound.wav"))
	{
		std::cout << "Problem z zaladowaniem dzwieku nr. 1";
	}
	menu_sound.setBuffer(MenuSound);

	sf::SoundBuffer MenuEnter;
	sf::Sound menu_enter;
	if (!MenuEnter.loadFromFile("Sounds/entermenu.ogg"))
	{
		std::cout << "Problem z zaladowaniem dzwieku nr. 1";
	}
	menu_enter.setBuffer(MenuEnter);

	std::vector<std::unique_ptr<RuchomySprite>> alien;

	for (int i = 0; i < 2; i++)
	{
		alien.emplace_back(std::make_unique<Duch>("Textures/chmurka.png"));
	}
	float pleaceX;
	float pleaceY;
	int direction;

	for (size_t i = 0; i < alien.size(); i++)
	{
		
		if (i == 1)
		{
			pleaceX = 30;
			pleaceY = 100;
		}
		else
		{
			pleaceX = 500;
			pleaceY = 50;
		}
		alien[i]->setPosition(pleaceX, pleaceY);
	}

	while (window.isOpen())
	{
		sf::Event event;
		elapsed = clock.restart();

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					menu_sound.play();
					menu.MoveUp();
					break;

				case sf::Keyboard::Down:
					menu_sound.play();
					menu.MoveDown();
					break;

				case sf::Keyboard::Return:
					menu_enter.play();
					switch (menu.GetPressedItem())
					{
					case 0:
					{
						
						Gra* gra = new Gra;
						while (gra->Run())
						{
							gra->Update();
							gra->Render();
						}
					}
						break;
					case 1:
					{
						Sterowanie* gra = new Sterowanie;
						while (gra->Run())
						{
							gra->Update();
							gra->Render();
						}

					}
						break;
					case 2:
						window.close();
						break;
					}

					break;
				}

				break;
			case sf::Event::Closed:
				window.close();

				break;

			}
		}
		for (size_t i = 0; i < alien.size(); i++)
		{
			alien[i]->Animuj2(elapsed);
		}


		window.clear();
		window.draw(sprite);
		for (size_t i = 0; i < alien.size(); i++)
		{
			window.draw(*alien[i]);
		}
		window.draw(sprite2);
		menu.draw(window);
		window.display();
	}
}