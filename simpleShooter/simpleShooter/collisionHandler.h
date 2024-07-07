#pragma once
#include "player.h"
#include "realMap.h"
#include "Bullet.h"
#include "allActiveBullets.h"
#include "activeDummies.h"
#include "Raycasting.h"
#include <list>
#include <thread>

class collisionHandler
{
private:
	std::shared_ptr<player> playerPointer;
	std::shared_ptr<realMap> mapWithObjects;
	
	std::unique_ptr<allActiveBullets> activeBullets;
	std::unique_ptr<activeDummies> aliveDummies;
	std::unique_ptr<Raycasting> activeRaycasting;

	bool handleCollionsPlayerWalls();
	bool handleCollisonBulletWalls();
	bool handleCollionBulletsEnemies();
	bool handleCollsionRayWalls();

public:
	collisionHandler(std::shared_ptr<player> playerPointer, std::shared_ptr<realMap> mapWithObjectsIni);
	
	void passBullets(std::unique_ptr<allActiveBullets> activeBulletsIni);
	std::unique_ptr<allActiveBullets> returnBullets();

	void passDummies(std::unique_ptr<activeDummies> activeDummiesIni);
	std::unique_ptr<activeDummies> returnDummies();

	void passRaycasting(std::unique_ptr<Raycasting> raycastingIni);
	std::unique_ptr<Raycasting> returnRaycasting();

	void kill();
	void handleCollisions();
};

