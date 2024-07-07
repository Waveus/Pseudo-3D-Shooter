#pragma once
#include "Scene.h"
#include "Mesh.h"
#include "realMap.h"
#include "player.h"
#include "collisionHandler.h"
#include "Bullet.h"
#include "allActiveBullets.h"
#include "activeDummies.h"
#include "Raycasting.h"
#include "Macros.h"
#define M_PI 3.14159265358979323846
class gameScene : public Scene
{
private:
	enumScene nextScene;
	std::shared_ptr<std::string> selectedMap;

	std::unordered_map<std::string, std::shared_ptr<sf::Texture>> Textures;
	std::unordered_map<std::string, std::shared_ptr<sf::Font>> Fonts;
	std::unordered_map<std::string, std::vector<std::string>> Maps;

	std::shared_ptr<Mesh> myMesh;
	std::shared_ptr<realMap> myMap;
	std::shared_ptr<player> myPlayer;
	std::shared_ptr<betterCounter> difficulty;
	
	std::unique_ptr<collisionHandler> myCollisionHandler;
	std::unique_ptr<allActiveBullets> activeBullets;
	std::unique_ptr<activeDummies> aliveDummies;
	std::unique_ptr<Raycasting> myRaycasting;

	std::vector<std::shared_ptr<sf::Texture>> pistolAnimation;
	int animationCounter;

	void handleKeyboard();
	void render2D();
	void render3D();
	
public:

	gameScene(std::shared_ptr<sf::RenderTarget> rendererIni, std::shared_ptr<ResourceManager> resourceManIni, std::shared_ptr<std::string> selectedMapIni, std::shared_ptr<betterCounter> difficultyIni);

	enumScene getNextScene();

	void reset();
	void run();
};

