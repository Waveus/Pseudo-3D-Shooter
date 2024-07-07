#pragma once
#include "Bullet.h"
#include <list>

class allActiveBullets : public sf::Drawable
{
private:
	std::list<std::unique_ptr<Bullet>> bulletList;
public:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		for (auto& bullet : bulletList)
		{
			target.draw(bullet->getEntity(), states);
		}
	}

	void moveBullets();
	std::list<std::unique_ptr<Bullet>>& getBulletList();
	void addToList(std::unique_ptr<Bullet> bulletToAdd);

};

