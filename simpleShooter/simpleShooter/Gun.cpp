#include "Gun.h"

bool Gun::trigger(sf::Vector2f bulletSpawn, float direction)
{
	if (this->cooldown.getinnerCounter() == 0)
	{
		this->bulletOfGun = std::make_unique<Bullet>(this->caliber, this->speedOfBullet, this->hpOfBullet, bulletSpawn, direction, this->colorOfBullets);
		this->bulletOfGun->moveDirectionBasedEntityRotationToMoveDirectionGlobal();
		this->bulletOfGun->normilizeMoveDirectionGlobal();
		this->cooldown.increment(100);
		return true;
	}
	return false;
}

Gun::Gun(int sizeBulletsIni, int speedIni, int hpIni, sf::Color colorOfBulletsIni)
{
	this->caliber = sizeBulletsIni;
	this->speedOfBullet = speedIni;
	this->hpOfBullet = hpIni;
	this->colorOfBullets = colorOfBulletsIni;
}

void Gun::decrementcooldown()
{
	this->cooldown.decrement(2);
}

std::unique_ptr<Bullet> Gun::getBullet()
{
	return std::move(this->bulletOfGun);
}
