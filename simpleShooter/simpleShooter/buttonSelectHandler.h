#pragma once
#include "betterButton.h"

class buttonSelectHandler
{
private:
	std::vector<std::shared_ptr<betterButton>> buttons;
	
	int selected;

	float horizontalPos;
	float firstButtonVerticalPos;
	float spacing;

public:
	buttonSelectHandler(float firstButtonVerticallyIni, float spacingIni);
	std::vector<std::shared_ptr<betterButton>> get();
	void add(std::shared_ptr<betterButton> x);

	std::string getSelectedButtonText();
	int getSelected();
	void next();
	void previous();
	void check();
	void uncheck();
	void changeSelectedText(std::string newString);
};

