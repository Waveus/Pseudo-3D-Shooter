#include "settingsScene.h"

settingsScene::settingsScene(std::shared_ptr<sf::RenderTarget> rendererIni, std::shared_ptr<ResourceManager> resourceManIni, std::shared_ptr<betterCounter> difficultyCounterIni)
{	
	this->renderer = rendererIni;
	this->resourceMan = resourceManIni;

	this->Fonts= this->resourceMan->getFonts();
	this->Textures = this->resourceMan->getTexturesBySet("settings");
	this->Music = this->resourceMan->getMusicBySet("music1");

	//Initializing select List
	//SCREENWIDTH, SCREENHEIGHT
	for (auto name : this->Music)
	{
		this->avaliableNamesOfMusic.push_back(name.first);
	}

	this->musicCounter = std::make_unique<betterCounter>(0, this->avaliableNamesOfMusic.size() - 1);

	this->selector = std::make_unique<buttonSelectHandler>(SCREENHEIGHT / 3, 70);
	this->selector->add(std::make_shared<betterButton>(this->Fonts["editundo"], "100"));
	this->selector->add(std::make_shared<betterButton>(this->Fonts["editundo"], "EASY"));
	this->selector->add(std::make_shared<betterButton>(this->Fonts["editundo"], this->avaliableNamesOfMusic[0]));
	this->selector->add(std::make_shared<betterButton>(this->Fonts["editundo"], "BACK"));

	this->selector->check();

	//Initializing static Text

	this->staticText.push_back(sf::Sprite(*this->Textures["settings"]));
	this->staticText.push_back(sf::Sprite(*this->Textures["volume"]));
	this->staticText.push_back(sf::Sprite(*this->Textures["difficulty"]));
 
	staticText[0].setOrigin(sf::Vector2f(staticText[0].getGlobalBounds().width / 2, staticText[0].getGlobalBounds().height / 2));
	staticText[0].move(sf::Vector2f(SCREENWIDTH / 2, SCREENHEIGHT / 4));

	staticText[1].setOrigin(sf::Vector2f(staticText[1].getGlobalBounds().width / 2, staticText[1].getGlobalBounds().height / 2));
	staticText[1].move(sf::Vector2f(SCREENWIDTH / 3, SCREENHEIGHT / 3));

	staticText[2].setOrigin(sf::Vector2f(staticText[2].getGlobalBounds().width / 2, staticText[2].getGlobalBounds().height / 2));
	staticText[2].move(sf::Vector2f(SCREENWIDTH / 3, SCREENHEIGHT / 3 + 70));
	
	//Initializing counters

	this->volumeCounter = std::make_unique<betterCounter>();
	this->difficultyCounter = difficultyCounterIni;

	//Setting difficulty levels

	this->textDifficulty.push_back("EASY");
	this->textDifficulty.push_back("MEDIUM");
	this->textDifficulty.push_back("HARD");

	this->Music[this->avaliableNamesOfMusic[this->musicCounter->getinnerCounter()]]->play();
	this->Music[this->avaliableNamesOfMusic[this->musicCounter->getinnerCounter()]]->setVolume(this->volumeCounter->getinnerCounter() / 2);
	this->Music[this->avaliableNamesOfMusic[this->musicCounter->getinnerCounter()]]->setLoop(true);
}


settingsScene::~settingsScene()
{

}

void settingsScene::render()
{
	for (auto& text : staticText)
	{
		this->renderer->draw(text);
	}

	for (auto& button : this->selector->get())
	{
		this->renderer->draw(*button);
	}
}

void settingsScene::captureKeyboardUpDown()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) 
	{
		if (this->clickedBeforeVertically == false)
		{
			this->selector->previous();
			this->clickedBeforeVertically = true;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (this->clickedBeforeVertically == false)
		{
			this->selector->next();
			this->clickedBeforeVertically = true;
		}
	}
	else
	{
		this->clickedBeforeVertically = false;
	}
}

void settingsScene::captureKeyboardLefRightEnter()
{
	//VOLUME LEVEL

	if (this->selector->getSelected() == 0)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			if (this->clickedBeforeHorizontally == false)
			{
				this->volumeCounter->decrement(5);
				std::cout << this->volumeCounter->getinnerCounter() << std::endl;
				this->selector->changeSelectedText(this->volumeCounter->getinnerCounterAsString());
				this->selector->check();

				this->clickedBeforeHorizontally = true;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			if (this->clickedBeforeHorizontally == false)
			{
				this->volumeCounter->increment(5);
				this->selector->changeSelectedText(this->volumeCounter->getinnerCounterAsString());
				this->selector->check();

				this->clickedBeforeHorizontally = true;
			}
		}
		else
		{
			this->clickedBeforeHorizontally = false;
		}
	}

	//DIFFICULTY LEVEL
	else if (this->selector->getSelected() == 1)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			if (this->clickedBeforeHorizontally == false)
			{

				this->difficultyCounter->decrement(1);

				this->selector->changeSelectedText(this->textDifficulty[this->difficultyCounter->getinnerCounter()-1]);
				this->selector->check();

				this->clickedBeforeHorizontally = true;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			if (this->clickedBeforeHorizontally == false)
			{
				this->difficultyCounter->increment(1);

				this->selector->changeSelectedText(this->textDifficulty[this->difficultyCounter->getinnerCounter()-1]);
				this->selector->check();

				this->clickedBeforeHorizontally = true;
			}
		}
		else
		{
			this->clickedBeforeHorizontally = false;
		}
	}
	//
	// TUUTUTUTUTUUT
	//
	else if (this->selector->getSelected() == 2)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			if (this->clickedBeforeHorizontally == false)
			{
				int buffer = musicCounter->getinnerCounter();
				this->musicCounter->decrement(1);

				if (buffer != this->musicCounter->getinnerCounter())
				{
					this->selector->changeSelectedText(this->avaliableNamesOfMusic[this->musicCounter->getinnerCounter()]);
					this->selector->check();

					this->Music[this->avaliableNamesOfMusic[buffer]]->stop();
					this->Music[this->avaliableNamesOfMusic[musicCounter->getinnerCounter()]]->play();
					this->Music[this->avaliableNamesOfMusic[musicCounter->getinnerCounter()]]->setLoop(true);
					this->Music[this->avaliableNamesOfMusic[musicCounter->getinnerCounter()]]->setVolume(this->volumeCounter->getinnerCounter() / 2);
				}
				this->clickedBeforeHorizontally = true;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			if (this->clickedBeforeHorizontally == false)
			{
				int buffer = musicCounter->getinnerCounter();
				this->musicCounter->increment(1);

				if (buffer != this->musicCounter->getinnerCounter())
				{
					this->selector->changeSelectedText(this->avaliableNamesOfMusic[this->musicCounter->getinnerCounter()]);
					this->selector->check();

					this->Music[this->avaliableNamesOfMusic[buffer]]->stop();
					this->Music[this->avaliableNamesOfMusic[musicCounter->getinnerCounter()]]->play();
					this->Music[this->avaliableNamesOfMusic[musicCounter->getinnerCounter()]]->setLoop(true);
					this->Music[this->avaliableNamesOfMusic[musicCounter->getinnerCounter()]]->setVolume(this->volumeCounter->getinnerCounter() / 2);
				}

				this->clickedBeforeHorizontally = true;
			}
		}
		else
		{
			this->clickedBeforeHorizontally = false;
		}
	}

	//BACK
	else if (this->selector->getSelectedButtonText() == "BACK") 
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			if (this->clickedBeforeHorizontally == false)
			{
				this->NextScene = enumScene::MENU;
				this->clickedBeforeHorizontally = true;
			}
		}
		else
		{
			this->clickedBeforeHorizontally = false;
		}
	}
}


enumScene settingsScene::getNextScene()
{
	return this->NextScene;
}

void settingsScene::reset()
{
	this->selector->previous();
	this->selector->previous();
	this->selector->previous();
	this->selector->previous();
	this->selector->previous();
	this->selector->previous();
	this->selector->previous();
	this->selector->previous();
}

void settingsScene::run()
{
	this->NextScene = enumScene::SETTINGS;

	this->captureKeyboardUpDown();
	this->captureKeyboardLefRightEnter();

	this->Music[this->avaliableNamesOfMusic[this->musicCounter->getinnerCounter()]]->setVolume(this->volumeCounter->getinnerCounter() / 2);

	this->render();
}
