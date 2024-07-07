#pragma once

//Basic includes
#include <memory>
#include <iostream>
#include <utility>
#include <unordered_map>

//SFML
#include "SFML/Graphics.hpp"

//Scenes
#include "Scene.h"
#include "menuScene.h"
#include "settingsScene.h"
#include "mapSelectScene.h"
#include "gameScene.h"
#include "exitScene.h"

//Others
#include "ResourceManager.h"
#include "enumScenes.h"
#include "Macros.h"
#include "betterCounter.h"

class Game
{
private:
	std::shared_ptr<sf::RenderWindow> gameWindow;
	std::shared_ptr<ResourceManager> rescourceMan;
	enumScene actualScene;

	std::unordered_map<enumScene, std::unique_ptr<Scene>> Scenes;
	std::shared_ptr<std::string> selectedMap;
	std::shared_ptr<betterCounter> difficulty;

	void initWindow();
	void initScenes();

public:

	Game(std::shared_ptr<ResourceManager> rescourceManIni) :
		rescourceMan(rescourceManIni),
		gameWindow(std::make_shared<sf::RenderWindow>(sf::VideoMode(SCREENWIDTH, SCREENHEIGHT), "ExaPix")),
		actualScene(enumScene::MENU){ this->initWindow(); this->initScenes(); } //TODO: MAYBE SINGLETON
	~Game();
	void run();
};

