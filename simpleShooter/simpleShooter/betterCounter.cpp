#include "betterCounter.h"

void betterCounter::increment(int incrementBy)
{
	if (this->innerCounter + incrementBy <= this->max && this->innerCounter + incrementBy >= this->min)
	{
		this->innerCounter += incrementBy;
	}
}

void betterCounter::decrement(int decrementBy)
{
	if (this->innerCounter - decrementBy <= this->max && this->innerCounter - decrementBy >= this->min)
	{
		this->innerCounter -= decrementBy;
	}
}

std::string betterCounter::getinnerCounterAsString()
{
	return std::to_string(this->innerCounter);
}

int betterCounter::getinnerCounter()
{
	return this->innerCounter;
}
