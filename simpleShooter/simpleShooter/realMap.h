#pragma once
#include "drawableTransformable.h"
#include <unordered_map>

class realMap : public drawableTransformable 
{
private:
	std::unordered_map<int, std::unordered_map<int, std::string>> wallTextures;
	std::vector<sf::RectangleShape> rectanglesWall;
	std::vector<sf::RectangleShape> dummies;
	std::unordered_map<int, std::unordered_map<int, bool>> isWall;
	sf::RectangleShape spawn;
	int spacing;

public:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		states.transform *= getTransform();
		for (auto& rectangle : rectanglesWall)
		{
			target.draw(rectangle, states);
		}
		for (auto& rectangle : dummies)
		{
			target.draw(rectangle, states);
		}
		target.draw(spawn, states);
	}

	realMap(std::vector<std::string> rawMap, int spacingIni);
	sf::Vector2f getSpawnPosition();
	sf::RectangleShape getSpawn();
	std::vector<sf::RectangleShape> getDummies();
	std::vector<sf::RectangleShape> getWalls();
	std::unordered_map<int, std::unordered_map<int, bool>>& getIsWall();
	std::string getWallTexture(int x, int y);

};

