#include "player.h"

std::unique_ptr<Bullet> player::getBullet()
{
	return std::move(this->GunOfPlayer->getBullet());
}

bool player::triggerGun()
{
	if(this->GunOfPlayer->trigger(this->entityBody.getPosition(), this->entityBody.getRotation())) return true;
	return false;
}

bool player::getMovedThisIteration()
{
	return this->movedThisIteration;
}

void player::keyboardHandler()
{
	this->moveDirectionBasedEntityRotation = sf::Vector2f(0, 0);
	this->movedThisIteration = false;
	this->GunOfPlayer->decrementcooldown();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->entityBody.rotate(-2);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->entityBody.rotate(2);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->moveDirectionBasedEntityRotation.x++;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->moveDirectionBasedEntityRotation.x--;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->moveDirectionBasedEntityRotation.y--;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->moveDirectionBasedEntityRotation.y++;
	}

	if (std::abs(this->moveDirectionBasedEntityRotation.x) + std::abs(this->moveDirectionBasedEntityRotation.y) > 0.2)
	{
		this->moveDirectionBasedEntityRotationToMoveDirectionGlobal();
		this->normilizeMoveDirectionGlobal();
		this->moveDirectionGlobalX();
		this->moveDirectionGlobalY();
	}
}
