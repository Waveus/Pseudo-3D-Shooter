#pragma once
#include "Scene.h"
#include "buttonSelectHandler.h"
#include "Macros.h"
#include <iostream>
#include <unordered_map>

#include "enumScenes.h"

class menuScene : public Scene
{
private:

	bool clickedBefore;
	enumScene nextScene;

protected:

	std::unordered_map<std::string, std::shared_ptr<sf::Font>> Fonts;
	std::unordered_map<std::string, std::shared_ptr<sf::Texture>> Textures;

	sf::Sprite title;

	std::unique_ptr<buttonSelectHandler> selector;

	void render();
	void captureKeyboard();

public:

	menuScene(std::shared_ptr<sf::RenderTarget> rendererIni, std::shared_ptr<ResourceManager> resourceManIni);
	~menuScene();

	enumScene getNextScene();
	
	void reset();
	void run();
	
};

