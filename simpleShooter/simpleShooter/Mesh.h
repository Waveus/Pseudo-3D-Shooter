#pragma once
#include "drawableTransformable.h"
#include "SFML/Graphics.hpp"
#include "Macros.h"

class Mesh : public drawableTransformable
{
public:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		states.transform *= getTransform();
		for (auto& rectangle : rectangles)
		{
			target.draw(rectangle, states);
		}
	}

	Mesh(int spacingIni);
	int getSpacing();
private:
	std::vector<sf::RectangleShape> rectangles;
	int spacing;
};

