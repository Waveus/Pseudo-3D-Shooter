#pragma once
#include "SFML/Graphics.hpp"
#include "entity.h"
#include <iostream>

# define M_PI           3.14159265358979323846

class Bullet : public entity
{
private:
	float direciton;
public:
	Bullet(int size, int speedIni, int hpIni, sf::Vector2f bulletSpawn, float direction, sf::Color colorOfBullet) : entity(size, speedIni, hpIni, bulletSpawn) {
		this->entityBody.setFillColor(colorOfBullet);
		this->entityBody.setRotation(direction);
		//std::cout << "Bullet direction: " << this->entityBody.getRotation() << std::endl;
		this->moveDirectionBasedEntityRotation = sf::Vector2f(1.f, 0.f);
		//this->entityBody.setRotation(direciton);
	};

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(this->entityBody, states);
	}

	//void move();
};

