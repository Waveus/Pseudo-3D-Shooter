#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

# define M_PI           3.14159265358979323846

class ray : public sf::Drawable
{
private:
	//sf::RectangleShape hitbox;
	sf::CircleShape rayBody;
	sf::Vector2f directionVector;
	sf::Vector2f startingPoint;
	//sf::Vector2i squarePosition;
	sf::Vector2f sideDistXY;
	sf::Vector2f deltaDistXY;
	sf::Vector2i actualSqare;
	bool hitWallVertically;
	int x, y;
	float meshSpacing;

	void directionToVector();

public:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(this->rayBody, states);
	}

	ray(float size, sf::Vector2f bulletSpawn, float direction, float meshSpacing, sf::Vector2i squarePositionIni, sf::Color colorOfBullet);
	
	sf::CircleShape getBody();
	//sf::RectangleShape getHitbox();
	sf::Vector2i getActualSquare();
	bool getHitVertically();
	void initRayPos();
	void move();
};

