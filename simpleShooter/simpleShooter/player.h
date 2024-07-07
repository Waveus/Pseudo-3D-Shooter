#pragma once
#include "drawableTransformable.h"
#include "entity.h"
#include "Gun.h"
#include "Macros.h"

#include <cmath>
#include <iostream>

# define M_PI           3.14159265358979323846

class player : public entity
{
private:

	bool movedThisIteration;
	std::unique_ptr<Gun> GunOfPlayer;
	std::unique_ptr<Bullet> shotBullet;

public:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(this->entityBody, states);
	}

	player(int size, int meshSpacing, int speedIni, int hpIni, sf::Vector2f playerSpawn, const sf::Texture* texture2D) : entity(size, speedIni, hpIni, playerSpawn) {
		this->entityBody.setTexture(texture2D);
		this->moveDirectionBasedEntityRotation = sf::Vector2f(0, 0);
		this->entityBody.move(meshSpacing / 2, meshSpacing / 2);
		this->hitbox.move(meshSpacing / 2, meshSpacing / 2);
		this->GunOfPlayer = std::make_unique<Gun>(5 / 1920.f * (float)SCREENWIDTH, 15.f / 1920.f * (float)SCREENWIDTH, 5, sf::Color::Red);
	};

	std::unique_ptr<Bullet> getBullet();
	bool triggerGun();
	void keyboardHandler();
	bool getMovedThisIteration();
};

