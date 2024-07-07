#include "Mesh.h"

Mesh::Mesh(int getSpacingIni)
{
	for (int i = 0; i < SCREENWIDTH; i += getSpacingIni)
	{
		sf::RectangleShape buffer;
		buffer.setSize(sf::Vector2f(1, SCREENHEIGHT));
		buffer.setPosition(i,0);
		this->rectangles.push_back(buffer);
	}

	for (int i = 0; i < SCREENHEIGHT; i += getSpacingIni)
	{
		sf::RectangleShape buffer;
		buffer.setSize(sf::Vector2f(SCREENWIDTH, 1));
		buffer.setPosition(0, i);
		this->rectangles.push_back(buffer);
	}
	this->spacing = getSpacingIni;
}

int Mesh::getSpacing()
{
	return this->spacing;
}

