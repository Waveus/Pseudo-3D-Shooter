#include "ray.h"

void ray::directionToVector()
{
	float rad = this->rayBody.getRotation() * M_PI / 180.0f;
	float cosB = std::cos(rad);
	float sinB = std::sin(rad);
	this->directionVector = sf::Vector2f(cosB, sinB);
}

ray::ray(float size, sf::Vector2f raySpawn, float direction, float meshSpacingIni, sf::Vector2i squarePositionIni, sf::Color colorOfBullet)
{
	this->rayBody.setRadius(size);
	this->rayBody.setOrigin(this->rayBody.getRadius(), this->rayBody.getRadius());
	this->rayBody.setPosition(raySpawn);
	this->rayBody.setFillColor(colorOfBullet);
	this->meshSpacing = meshSpacingIni;
	this->rayBody.setRotation(direction);
	this->startingPoint = raySpawn;
	this->directionToVector();

	this->actualSqare = squarePositionIni;
	this->deltaDistXY = sf::Vector2f(abs(meshSpacingIni / this->directionVector.x), abs(meshSpacingIni / this->directionVector.y));
}

bool ray::getHitVertically()
{
	return this->hitWallVertically;
}

void ray::initRayPos()
{
	if (this->directionVector.x >= 0)
	{
		sideDistXY.x = (this->actualSqare.x - (this->rayBody.getPosition().x - this->meshSpacing)) / this->directionVector.x;
	}
	else 
	{
		sideDistXY.x = (this->rayBody.getPosition().x - this->actualSqare.x) / this->directionVector.x * -1;
	}

	if (this->directionVector.y >= 0)
	{
		sideDistXY.y = (this->actualSqare.y - (this->rayBody.getPosition().y - this->meshSpacing)) / this->directionVector.y;
	}
	else
	{
		sideDistXY.y = (this->rayBody.getPosition().y - this->actualSqare.y) / this->directionVector.y * -1;
	}

	if (this->directionVector.x > 0)
	{
		this->x = 1;
	}
	else
	{
		this->x = -1;
	}

	if (this->directionVector.y > 0)
	{
		this->y = 1;
	}
	else
	{
		this->y = -1;
	}
}

void ray::move()
{
	if (abs(this->sideDistXY.x) < abs(this->sideDistXY.y))
	{
		this->rayBody.setPosition(this->startingPoint.x + this->sideDistXY.x * this->directionVector.x, this->startingPoint.y + this->sideDistXY.x * this->directionVector.y);
		sideDistXY.x += this->deltaDistXY.x;
		this->actualSqare.x += meshSpacing * x;
		hitWallVertically = true;
	}
	else 
	{
		this->rayBody.setPosition(this->startingPoint.x + this->sideDistXY.y * this->directionVector.x, this->startingPoint.y + this->sideDistXY.y * this->directionVector.y);
		sideDistXY.y += this->deltaDistXY.y;
		this->actualSqare.y += meshSpacing * y;
		hitWallVertically = false;
	}
} 

sf::Vector2i ray::getActualSquare()
{
	return this->actualSqare;
}

sf::CircleShape ray::getBody()
{
	return this->rayBody;
}
