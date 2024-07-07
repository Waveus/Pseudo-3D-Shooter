#pragma once
#include "drawableTransformable.h"

class betterButton : public drawableTransformable
{
private:
public:

	betterButton(std::shared_ptr<sf::Font> font, std::string text);
	void check(sf::Color changeColor);
	void uncheck();
	void changeString(std::string newString);
	std::string getText();
protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		states.transform *= getTransform();
		target.draw(background, states);
		target.draw(text, states);
	}

	sf::Color innerColor;
	sf::Text text;
	sf::RectangleShape background;
};

