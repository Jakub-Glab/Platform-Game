#include "Sterowanie.h"

Sterowanie::Sterowanie()
{
	window = new sf::RenderWindow(sf::VideoMode(800, 800), "STEROWANIE");
}
void Sterowanie::loadTextures()
{
	tlo.loadFromFile("tlo5.png");
}
void Sterowanie::loadData()
{
	loadTextures();
}
bool Sterowanie::Run()
{
	return window->isOpen();
}
void Sterowanie::Update()
{
	window->setFramerateLimit(30);
	while (window->pollEvent(evnt)) {

		switch (evnt.type) {

		case sf::Event::Closed:
			window->close();
			break;
		}
	}
}
void Sterowanie::Render()
{
	Sprite.setTexture(tlo);

	window->clear();

	window->draw(Sprite);

	Sprite.setPosition(0, 0);

	window->display();
}