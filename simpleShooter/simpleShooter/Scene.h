#pragma once
#include "SFML/Graphics.hpp"
#include "ResourceManager.h"
#include "enumScenes.h"
#include <iostream>

class Scene
{
protected:
	std::shared_ptr<ResourceManager> resourceMan;
	std::shared_ptr<sf::RenderTarget> renderer;
public:

	virtual ~Scene();

	virtual enumScene getNextScene() = 0;
	virtual void run() = 0;
	virtual void reset() = 0;
};

