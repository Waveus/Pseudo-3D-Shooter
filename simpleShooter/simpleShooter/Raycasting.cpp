#include "Raycasting.h"
#include "Macros.h"

Raycasting::Raycasting(float raysSizeIni, float FOVIni, float meshSpacing, sf::Color raysColorIni)
{
	this->FOV = FOVIni;
	this->meshSpacing = meshSpacing;
	this->raysColor = raysColorIni;
	this->raysSize = raysSizeIni;

}

std::list<std::unique_ptr<ray>>& Raycasting::getRays()
{
	return this->Rays;
}

void Raycasting::castRays(sf::Vector2f positionIni, float directionIni)
{
	this->playerDirection = directionIni;
	this->position = positionIni;
	this->squarePosition = sf::Vector2i((((int)this->position.x) / meshSpacing) * meshSpacing, (((int)this->position.y) / meshSpacing) * meshSpacing);

	this->Rays.clear();

	for (int i = 0; i < SCREENWIDTH; i++)
	{
		this->Rays.push_back(std::make_unique<ray>(this->raysSize, positionIni, directionIni - FOV/2 + ((float)i * FOV / SCREENWIDTH), this->meshSpacing, this->squarePosition, this->raysColor));
	}
}

void Raycasting::InitPos()
{
	for (auto& ray : this->Rays)
	{
		ray->initRayPos();
	}
}

void Raycasting::moveRays()
{
	for (auto& ray : this->Rays)
	{
		ray->move();
	}
}

