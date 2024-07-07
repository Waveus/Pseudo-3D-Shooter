#pragma once
#include "Scene.h"
class exitScene : public Scene
{
public:
	enumScene getNextScene();
	void reset();
	void run();
};

