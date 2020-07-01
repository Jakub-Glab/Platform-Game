#include <SFML/Graphics.hpp>
#include "Gra.h"

int main()
{

	Gra* gra = new Gra;
	while (gra->Run())
	{
		gra->Update();
		gra->Render();
	}

	return 0;
}