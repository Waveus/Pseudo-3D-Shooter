#include "realMap.h"

realMap::realMap(std::vector<std::string> rawMap , int spacingIni)
{
	this->spacing = spacingIni;
	sf::Vector2f posXY(0,0);
	for (auto& line : rawMap)
	{
		posXY.x = 0;
		for (auto& character : line)
		{
			isWall[posXY.x][posXY.y] = false;

			if (character == 'S')
			{
				sf::RectangleShape buffer(sf::Vector2f(spacingIni, spacingIni));
				buffer.setFillColor(sf::Color::Red);
				buffer.setPosition(posXY);
				this->spawn = buffer;
			}
			else if (character == 'D')
			{
				sf::RectangleShape buffer(sf::Vector2f(spacingIni, spacingIni));
				buffer.setFillColor(sf::Color(100,10,30));
				buffer.setPosition(posXY);
				this->dummies.push_back(buffer);
			}
			else if (character == ' ')
			{

			}
			else 
			{
				sf::RectangleShape buffer;
				buffer.setSize(sf::Vector2f(spacingIni, spacingIni));
				buffer.setFillColor(sf::Color::Green);
				buffer.setPosition(posXY);
				this->rectanglesWall.push_back(buffer);
				isWall[posXY.x][posXY.y] = true;
				this->wallTextures[posXY.x][posXY.y] = character;
			}
			posXY.x += spacingIni;
		}
		posXY.y += spacingIni;
	}
}

sf::Vector2f realMap::getSpawnPosition()
{
	return this->spawn.getPosition();
}

sf::RectangleShape realMap::getSpawn()
{
	return this->spawn;
}

std::vector<sf::RectangleShape> realMap::getDummies()
{
	return this->dummies;
}

std::vector<sf::RectangleShape> realMap::getWalls()
{
	return this->rectanglesWall;
}

std::unordered_map<int, std::unordered_map<int, bool>>& realMap::getIsWall()
{
	return this->isWall;
}

std::string realMap::getWallTexture(int x, int y)
{
	return this->wallTextures[x][y];
}
