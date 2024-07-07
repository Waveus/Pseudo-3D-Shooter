#include "counter.h"

void counter::updateTexture()
{
	std::vector<int> unitsHundredsEtc;
	for (int i = 1; i <= this->max; i *= 10)
	{
		unitsHundredsEtc.push_back((this->innerCounter / i) % 10);
	}
	std::reverse(unitsHundredsEtc.begin(), unitsHundredsEtc.end());

	for (int i = 0; i < this->digits2.size();i++)
	{
		this->digits2[i].setTexture(*this->textures2[std::to_string(unitsHundredsEtc[i])]);
	}
}

void counter::moveCounter2(float x, float y)
{
	for (auto& i : this->digits2)
	{
		i.move(x, y);
	}
}

sf::Sprite& counter::getToModifyByNr(int nr)
{
	return this->digits2[nr];
}

sf::Sprite counter::getSpriteByNr(int nr)
{
	return this->digits2[nr];
}

std::vector<sf::Sprite> counter::getVectorOfSprites()
{
	return this->digits2;
}

void counter::increment(int incrementBy)
{
	if (this->innerCounter + incrementBy <= this->max && this->innerCounter + incrementBy >= this->min)
	{
		this->innerCounter += incrementBy;
		this->updateTexture();
	}
}

void counter::decrement(int decrementBy)
{
	if (this->innerCounter - decrementBy <= this->max && this->innerCounter - decrementBy >= this->min)
	{
		this->innerCounter -= decrementBy;
		this->updateTexture();
	}
}

int counter::getInnerCounter()
{
	return this->innerCounter;
}

