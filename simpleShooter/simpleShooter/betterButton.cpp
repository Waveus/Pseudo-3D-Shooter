#include "betterButton.h"

betterButton::betterButton(std::shared_ptr<sf::Font> font, std::string text)
{
	this->innerColor = sf::Color(0, 134, 212);

	this->text.setFont(*font);
	this->text.setCharacterSize(50);
	this->text.setString(text);
	this->text.setFillColor(this->innerColor);
	this->text.setOrigin(this->text.getGlobalBounds().getSize().x / 2, this->text.getGlobalBounds().getSize().y * 1.1);
	this->background.setOrigin(this->background.getSize().x / 2, this->background.getSize().y / 2);
}

void betterButton::check(sf::Color changeColor)
{
	this->text.setFillColor(changeColor);
}

void betterButton::uncheck()
{
	this->text.setFillColor(this->innerColor);
}

void betterButton::changeString(std::string newString)
{
	this->text.setString(newString);
}

std::string betterButton::getText()
{
	return this->text.getString();
}



