#include "allActiveBullets.h"

void allActiveBullets::moveBullets()
{
	for (auto& bullet : this->bulletList)
	{
		bullet->moveDirectionGlobalX();
		bullet->moveDirectionGlobalY();
	}
}

std::list<std::unique_ptr<Bullet>>& allActiveBullets::getBulletList()
{
	return this->bulletList;
}

void allActiveBullets::addToList(std::unique_ptr<Bullet> bulletToAdd)
{
	this->bulletList.push_back(std::move(bulletToAdd));
}
