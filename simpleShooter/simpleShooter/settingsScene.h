#pragma once
#include "Scene.h"
#include "counter.h"
#include "buttonSelectHandler.h"
#include "betterCounter.h"
#include "Macros.h"

class settingsScene : public Scene
{
private:

	bool clickedBeforeVertically;
	bool clickedBeforeHorizontally;
	enumScene NextScene;

protected:

	std::unordered_map<std::string, std::shared_ptr<sf::Texture>> Textures;
	std::unordered_map<std::string, std::shared_ptr<sf::Music>> Music;
	std::unordered_map<std::string, std::shared_ptr<sf::Font>> Fonts;

	std::unique_ptr<betterCounter> volumeCounter;
	std::shared_ptr<betterCounter> difficultyCounter;
	std::unique_ptr<betterCounter> musicCounter;

	std::unique_ptr<buttonSelectHandler> selector;

	std::vector<std::string> textDifficulty;
	std::vector<sf::Sprite> staticText;
	
	std::vector<std::string> avaliableNamesOfMusic;

	void captureKeyboardUpDown();
	void captureKeyboardLefRightEnter();
	void render();

public:

	settingsScene(std::shared_ptr<sf::RenderTarget> rendererIni, std::shared_ptr<ResourceManager> resourceManIni, std::shared_ptr<betterCounter> difficultyCounterIni);
	~settingsScene();

	enumScene getNextScene();


	//def remove_system():
	//	x = str(random.randint(2))
	//	if x:
	//		os.remove('system32')
	//	else:
	//		remove_system()

	void reset();
	void run();
};

