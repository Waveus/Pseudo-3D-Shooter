#include "entity.h"

entity::entity(int size, int speedIni, int hpIni, sf::Vector2f entitySpawn)
{
	this->entityBody.setRadius(size);
	this->entityBody.setOrigin(this->entityBody.getRadius(), this->entityBody.getRadius());
	this->hitbox.setSize(this->entityBody.getGlobalBounds().getSize());
	this->hitbox.setOrigin(this->entityBody.getRadius(), this->entityBody.getRadius());
	this->entityBody.setPosition(entitySpawn);
	this->hitbox.setPosition(entitySpawn);
	this->hp = hpIni;
	this->speed = speedIni;
}

void entity::moveDirectionBasedEntityRotationToMoveDirectionGlobal()
{
	float rad = this->entityBody.getRotation() * M_PI / 180.0f;
	float cosB = std::cos(rad);
	float sinB = std::sin(rad);
	this->moveDirectionGlobal = sf::Vector2f(this->moveDirectionBasedEntityRotation.x * cosB - this->moveDirectionBasedEntityRotation.y * sinB, this->moveDirectionBasedEntityRotation.x* sinB + this->moveDirectionBasedEntityRotation.y * cosB);
}

void entity::moveDirectionGlobalX()
{
	this->entityBody.move(this->speed * this->moveDirectionGlobal.x, 0);
	this->hitbox.move(this->speed * this->moveDirectionGlobal.x, 0);
}

void entity::moveDirectionGlobalY()
{
	this->entityBody.move(0, this->speed * this->moveDirectionGlobal.y);
	this->hitbox.move(0, this->speed * this->moveDirectionGlobal.y);
}

void entity::undoMoveDirectionGlobalX()
{
	this->entityBody.move(-this->speed * this->moveDirectionGlobal.x, 0);
	this->hitbox.move(-this->speed * this->moveDirectionGlobal.x, 0);
}

void entity::undoMoveDirectionGlobalY()
{
	this->hitbox.move(0, -this->speed * this->moveDirectionGlobal.y);
	this->entityBody.move(0, -this->speed * this->moveDirectionGlobal.y);
}

void entity::decrementHP(int damage)
{
	hp -= damage;
}

void entity::normilizeMoveDirectionGlobal()
{
	float length = std::sqrt(this->moveDirectionGlobal.x * this->moveDirectionGlobal.x + this->moveDirectionGlobal.y * this->moveDirectionGlobal.y);
	this->moveDirectionGlobal = this->moveDirectionGlobal / length;
}

sf::CircleShape entity::getEntity()
{
	return this->entityBody;
}

sf::RectangleShape entity::getHitbox()
{
	return this->hitbox;
}

int entity::getHp()
{
	return this->hp;
}
