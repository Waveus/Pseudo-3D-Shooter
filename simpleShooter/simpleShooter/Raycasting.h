#pragma once
#include "ray.h"
#include "SFML/Graphics.hpp"
#include <list>

class Raycasting : public sf::Drawable
{
private:

	float playerDirection;
	float FOV;
	int meshSpacing;
	float raysSize;

	sf::Vector2i squarePosition;
	sf::Vector2f position;
	sf::Color raysColor;
	std::list<std::unique_ptr<ray>> Rays;

public:
	Raycasting(float raysSizeIni, float FOVIni, float meshSpacing, sf::Color raysColorIni);
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		for (auto& ray : Rays)
		{
			target.draw(ray->getBody(), states);
		}
	}

	std::list<std::unique_ptr<ray>>& getRays();
	void castRays(sf::Vector2f positionIni, float directionIni);
	void InitPos();
	void moveRays();
};

