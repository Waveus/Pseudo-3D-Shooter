#include "menuScene.h"


menuScene::menuScene(std::shared_ptr<sf::RenderTarget> rendererIni, std::shared_ptr<ResourceManager> resourceManIni)
{
	this->renderer = rendererIni;
	this->resourceMan = resourceManIni;

	this->Textures = this->resourceMan->getTexturesBySet("menu");
	this->Fonts = this->resourceMan->getFonts();

	this->clickedBefore = 1;

	//initializing title

	title.setTexture(*Textures["title"]);
	title.setOrigin(sf::Vector2f(title.getGlobalBounds().width / 2, title.getGlobalBounds().height / 2));
	title.move(sf::Vector2f(SCREENWIDTH / 2, SCREENHEIGHT / 4));

	//Buttons select

	this->selector = std::make_unique<buttonSelectHandler>(SCREENHEIGHT /3, 70);
	this->selector->add(std::make_shared<betterButton>(this->Fonts["editundo"], "PLAY"));
	this->selector->add(std::make_shared<betterButton>(this->Fonts["editundo"], "SETTINGS"));
	this->selector->add(std::make_shared<betterButton>(this->Fonts["editundo"], "EXIT"));

	this->selector->check();
}

enumScene menuScene::getNextScene()
{
	return this->nextScene;
}

void menuScene::render()
{
	for (auto& button : this->selector->get())
	{
		this->renderer->draw(*button);
	}
	this->renderer->draw(title);
}

void menuScene::captureKeyboard()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))	
	{
		if (not clickedBefore)
		{
			this->selector->previous();
			this->clickedBefore = true;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (not clickedBefore)
		{
			this->selector->next();
			this->clickedBefore = true;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		if (not clickedBefore)
		{
			if (this->selector->getSelectedButtonText() == "EXIT")
			{
				this->nextScene = enumScene::EXIT;
			}
			else if (this->selector->getSelectedButtonText() == "PLAY")
			{
				this->nextScene = enumScene::SELECTMAP ;
			}
			else if (this->selector->getSelectedButtonText() == "SETTINGS")
			{
				this->nextScene = enumScene::SETTINGS;
			}
			this->clickedBefore = true;
		}
	}
	else
	{
		this->clickedBefore = false;
	}
}

void menuScene::reset()
{
	this->selector->previous();
	this->selector->previous();
	this->selector->previous();
	this->selector->previous();
}

void menuScene::run()
{
	this->nextScene = enumScene::MENU;
	this->render();
	this->captureKeyboard();
}

menuScene::~menuScene()
{
	std::cout << "Bye menuScene" << std::endl;
}
