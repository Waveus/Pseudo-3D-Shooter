#include <iostream>
#include <memory>
#include "Game.h"
#include "drawableTransformable.h"

#include "ResourceManager.h"
#include <SFML/Graphics.hpp>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "betterButton.h"

int main(int argc, char** argv)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	std::shared_ptr<ResourceManager> resourceman;

	resourceman = std::make_shared<ResourceManager>("resources");

	sf::Text tekst;

	tekst.getGlobalBounds();
	sf::RectangleShape rect;

	Game game(resourceman);
	game.run();
}

