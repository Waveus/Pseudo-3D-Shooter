#pragma once
#include "Bullet.h"
#include "betterCounter.h"

class Gun
{
private:
	std::unique_ptr<Bullet> bulletOfGun;
	sf::Color colorOfBullets;
	int caliber;
	int speedOfBullet;
	int hpOfBullet; //Also DMG that makes
	betterCounter cooldown;


public:

	bool trigger(sf::Vector2f bulletSpawn, float direction);
	Gun(int size, int speedIni, int hpInithi, sf::Color colorOfBulletsIni);
	
	void decrementcooldown();
	std::unique_ptr<Bullet> getBullet();
};

