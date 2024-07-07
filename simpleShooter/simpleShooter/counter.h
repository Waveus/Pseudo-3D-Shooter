#pragma once

#include "SFML/Graphics.hpp"
#include "unordered_map"
#include <vector>
#include <cmath>
#include <algorithm>
#include <sstream>


class counter
{
private:

	std::vector<std::shared_ptr<sf::Texture>> textures;
	std::tuple<sf::Sprite, sf::Sprite, sf::Sprite> digits;
	
	int innerCounter;
	int min, max;

	std::unordered_map<std::string, std::shared_ptr<sf::Texture>> textures2;
	std::vector<sf::Sprite> digits2;

	void updateTexture();

public:
	
	counter(std::unordered_map<std::string, std::shared_ptr<sf::Texture>> texturesIni, int nrOfDigits, int minIni, int maxIni)	:
	max(maxIni),
	min(minIni),
	digits2(nrOfDigits)
	{
		this->textures2 = texturesIni;
		if (std::log10(maxIni) + 1 > nrOfDigits || minIni < maxIni)
		{
			this->max = 100;
			this->min = 0;
			this->digits2.reserve(3);
		}
		for (auto& digit : digits2)
		{
			digit.setTexture(*this->textures2["nine"]);
		}
		for (int i = 1; i < this->digits2.size(); i++)
		{
			this->digits2[i].setPosition(i * this->digits2[i - 1].getGlobalBounds().width, 0);
		}

		this->innerCounter = max;
		this->updateTexture();
	};

	counter(std::unordered_map<std::string, std::shared_ptr<sf::Texture>> texturesIni) :
		digits2(3), min(0), max(100) {
		this->innerCounter = max;
		this->textures2 = texturesIni;
		for (auto& digit : digits2)
		{
			digit.setTexture(*this->textures2["9"]);
		}
		for (int i = 1; i < this->digits2.size(); i++)
		{
			this->digits2[i].setPosition(i * this->digits2[i - 1].getGlobalBounds().width, 0);
		}

		this->innerCounter = max;
		this->updateTexture();
	};

	void moveCounter2(float x, float y);

	sf::Sprite& getToModifyByNr(int nr);
	sf::Sprite getSpriteByNr(int nr);
	std::vector<sf::Sprite> getVectorOfSprites();

	void increment(int incrementBy);
	void decrement(int decrementBy);
	int getInnerCounter();

};

