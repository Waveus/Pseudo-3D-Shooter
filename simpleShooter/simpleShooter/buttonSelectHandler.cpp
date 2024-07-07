#include "buttonSelectHandler.h"
#include "Macros.h"

void buttonSelectHandler::check()
{
	this->buttons[this->selected]->check(sf::Color::Magenta);
}

void buttonSelectHandler::uncheck()
{
	this->buttons[this->selected]->uncheck();
}

void buttonSelectHandler::changeSelectedText(std::string newString)
{
	this->buttons[this->selected]->changeString(newString);
}

buttonSelectHandler::buttonSelectHandler(float firstButtonVerticallyIni, float spacingIni)
{
	this->selected = 0;
	this->horizontalPos = SCREENWIDTH / 2;
	this->firstButtonVerticalPos = firstButtonVerticallyIni;
	this->spacing = spacingIni;
}

std::vector<std::shared_ptr<betterButton>> buttonSelectHandler::get()
{
	return this->buttons;
}

void buttonSelectHandler::add(std::shared_ptr<betterButton> toAdd)
{
	this->buttons.push_back(toAdd);
	this->buttons[this->buttons.size() - 1]->move(this->horizontalPos, this->firstButtonVerticalPos + this->spacing * (this->buttons.size() - 1));
}

std::string buttonSelectHandler::getSelectedButtonText()
{
	return buttons[selected]->getText();
}

int buttonSelectHandler::getSelected()
{
	return this->selected;
}

void buttonSelectHandler::next()
{
	if (this->selected + 1 < this->buttons.size())
	{
		this->uncheck();
		this->selected++;
		this->check();
	}
}

void buttonSelectHandler::previous()
{
	if (this->selected - 1 >= 0)
	{
		this->uncheck();
		this->selected--;
		this->check();
	}
}


