#pragma once
#include<SFML/Graphics.hpp>

class drawableTransformable : public sf::Drawable, public sf::Transformable
{
public:
	virtual ~drawableTransformable() = default;
};

