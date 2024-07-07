#pragma once
#include "dummy.h"
#include <list>
#include "drawableTransformable.h"

class activeDummies : public sf::Drawable
{
private:
	std::list<std::unique_ptr<dummy>> dummies;
public:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		for (auto& dummy : dummies)
		{
			target.draw(dummy->getEntity(), states);
		}
	}

	void addDummy(std::unique_ptr<dummy> dummyToAdd);
	std::list<std::unique_ptr<dummy>>& getDummyList();
	void clear();
};

