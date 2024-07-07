#pragma once
#include <string>

class betterCounter
{
private:

	int innerCounter;
	int min;
	int max;

public:
	betterCounter() : innerCounter(100), min(0), max(100) {};

	betterCounter(int min, int max) : innerCounter(min), min(min), max(max) {};

	void increment(int incrementBy);
	void decrement(int decrementBy);

	std::string getinnerCounterAsString();
	int getinnerCounter();
};

