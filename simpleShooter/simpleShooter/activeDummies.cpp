#include "activeDummies.h"

void activeDummies::addDummy(std::unique_ptr<dummy> dummyToAdd)
{
	this->dummies.push_back(std::move(dummyToAdd));
}

std::list<std::unique_ptr<dummy>>& activeDummies::getDummyList()
{
	return this->dummies;
}

void activeDummies::clear()
{
	this->dummies.clear();
}
