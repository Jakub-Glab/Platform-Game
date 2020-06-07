#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
	Game* game = new Game;
	while (game->Run())
	{
		game->Update();
		game->Render();
	}

	return 0;
}