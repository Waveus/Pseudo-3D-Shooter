#pragma once
#include "Scene.h"
#include "betterButton.h"
#include "buttonSelectHandler.h"
#include "Macros.h"


class mapSelectScene : public Scene
{
private:
	bool clickedBefore;
	enumScene nextScene;
protected:

	sf::Sprite title;

	std::unordered_map<std::string, std::shared_ptr<sf::Texture>> Textures;
	std::unordered_map<std::string, std::shared_ptr<sf::Font>> Fonts;
	std::unordered_map<std::string, std::vector<std::string>> Maps;
	
	std::shared_ptr<std::string> selectedMap;

	std::unique_ptr<buttonSelectHandler> selector;

	void handleKeyboard();
	void render();

public:

	mapSelectScene(std::shared_ptr<sf::RenderTarget> rendererIni, std::shared_ptr<ResourceManager> resourceManIni, std::shared_ptr<std::string> selectedMapIni);
	
	enumScene getNextScene();
	
	void reset();
	void run();
};

