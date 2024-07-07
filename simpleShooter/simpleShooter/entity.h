#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

# define M_PI           3.14159265358979323846

class entity : public sf::Drawable
{
protected:

	int hp;
	float speed;

	sf::RectangleShape hitbox;
	sf::CircleShape entityBody;
	sf::Vector2f moveDirectionBasedEntityRotation;
	sf::Vector2f moveDirectionGlobal;

public:
	//entity(int speedIni, int hpIni, sf::Vector2f entitySpawn);
	entity(int size, int speedIni, int hpIni, sf::Vector2f entitySpawn);

	void normilizeMoveDirectionGlobal();
	void moveDirectionBasedEntityRotationToMoveDirectionGlobal();
	void moveDirectionGlobalX();
	void moveDirectionGlobalY();
	void undoMoveDirectionGlobalX();
	void undoMoveDirectionGlobalY();
	void decrementHP(int damage);

	sf::CircleShape getEntity();
	sf::RectangleShape getHitbox();
	int getHp();
};

