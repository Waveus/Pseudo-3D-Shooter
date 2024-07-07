#include "collisionHandler.h"

bool collisionHandler::handleCollionsPlayerWalls()
{
	if (this->playerPointer->getMovedThisIteration()) return false;

	for (auto& wall : this->mapWithObjects->getWalls())
	{
		if (wall.getGlobalBounds().intersects(this->playerPointer->getHitbox().getGlobalBounds()))
		{
			return true;
		}
	}
	return false;
}

bool collisionHandler::handleCollisonBulletWalls()
{
	for (auto& wall : this->mapWithObjects->getWalls())
	{
		for (auto& bullet : activeBullets->getBulletList())
		{
			if (wall.getGlobalBounds().intersects(bullet->getHitbox().getGlobalBounds()))
			{
				bullet->decrementHP(999);
			}
		}
	}
	return false;
}

bool collisionHandler::handleCollionBulletsEnemies()
{
	for (auto& bullet : activeBullets->getBulletList())
	{
		for (auto& dummy : aliveDummies->getDummyList())
		{
			if (bullet->getHitbox().getGlobalBounds().intersects(dummy->getHitbox().getGlobalBounds()))
			{
				dummy->decrementHP(bullet->getHp());
			}
		}
	}
	return false;
}

bool collisionHandler::handleCollsionRayWalls()
{
	bool found = false;

	for (auto& ray : this->activeRaycasting->getRays())
	{
		found = false;
		while (not found)
		{
			ray->move();
			sf::Vector2i i = ray->getActualSquare();
			if (this->mapWithObjects->getIsWall()[i.x][i.y]) found = true;
		}
	}

	return 1;
}



collisionHandler::collisionHandler(std::shared_ptr<player> playerPointer, std::shared_ptr<realMap> mapWithObjectsIni)
{
	this->mapWithObjects = mapWithObjectsIni;
	this->playerPointer = playerPointer;
}

void collisionHandler::passBullets(std::unique_ptr<allActiveBullets> activeBulletsIni)
{
	this->activeBullets = std::move(activeBulletsIni);
}

std::unique_ptr<allActiveBullets> collisionHandler::returnBullets()
{
	return std::move(this->activeBullets);
}

void collisionHandler::passDummies(std::unique_ptr<activeDummies> activeDummiesIni)
{
	this->aliveDummies = std::move(activeDummiesIni);
}

std::unique_ptr<activeDummies> collisionHandler::returnDummies()
{
	return std::move(this->aliveDummies);
}

void collisionHandler::passRaycasting(std::unique_ptr<Raycasting> raycastingIni)
{
	this->activeRaycasting = std::move(raycastingIni);
}

std::unique_ptr<Raycasting> collisionHandler::returnRaycasting()
{
	return std::move(this->activeRaycasting);
}

void collisionHandler::kill()
{
	if (this->playerPointer->getHp() <= 0) throw std::runtime_error("Player IS DEADDDDDDDDDDD");
	
	for (auto it = this->activeBullets->getBulletList().begin(); it != this->activeBullets->getBulletList().end();) {
		if (it->get()->getHp() <= 0) {
			it = this->activeBullets->getBulletList().erase(it); 
		}
		else {
			++it; 
		}
	}

	for (auto it = this->aliveDummies->getDummyList().begin(); it != this->aliveDummies->getDummyList().end();) {
		if (it->get()->getHp() <= 0) {
			it = this->aliveDummies->getDummyList().erase(it);
		}
		else {
			++it;
		}
	}
}

void collisionHandler::handleCollisions()
{
	if (this->handleCollionsPlayerWalls())
	{
		this->playerPointer->undoMoveDirectionGlobalX();

		if (this->handleCollionsPlayerWalls())
		{	
			this->playerPointer->undoMoveDirectionGlobalY();
			this->playerPointer->moveDirectionGlobalX();
			if (this->handleCollionsPlayerWalls())
			{
				this->playerPointer->undoMoveDirectionGlobalX();
			}
		}
	}

	std::thread t3(&collisionHandler::handleCollsionRayWalls, this);
	std::thread t(&collisionHandler::handleCollisonBulletWalls, this);
	std::thread t2(&collisionHandler::handleCollionBulletsEnemies, this);
	t.join();
	t3.join();
	t2.join();
	this->kill();



	
}
