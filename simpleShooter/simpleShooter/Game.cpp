#include "Game.h"

void Game::initWindow()
{
    this->selectedMap = std::make_shared<std::string>("AAA");
    this->difficulty = std::make_shared<betterCounter>(1,3);
    gameWindow->setTitle("Pixel Rush");
	gameWindow->setFramerateLimit(60);
	gameWindow->setVerticalSyncEnabled(true);
}

void Game::initScenes()
{
    this->Scenes[enumScene::EXIT] = (std::make_unique<exitScene>());
    this->Scenes[enumScene::MENU] = (std::make_unique<menuScene>(gameWindow, this->rescourceMan));
    this->Scenes[enumScene::SETTINGS] = (std::make_unique<settingsScene>(gameWindow, this->rescourceMan, this->difficulty));
    this->Scenes[enumScene::SELECTMAP] = (std::make_unique<mapSelectScene>(gameWindow, this->rescourceMan, this->selectedMap));
    this->Scenes[enumScene::GAME] = (std::make_unique<gameScene>(gameWindow, this->rescourceMan, this->selectedMap, this->difficulty));
}

//Game Constructor in .h

Game::~Game()
{
}

void Game::run()
{
    while (gameWindow->isOpen())
    {
        sf::Event event;
        while (gameWindow->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                gameWindow->close();
        }

        gameWindow->clear();
        
        this->Scenes[this->actualScene]->run();

        if (this->actualScene != this->Scenes[this->actualScene]->getNextScene())
        {
            this->actualScene = this->Scenes[this->actualScene]->getNextScene();
            this->Scenes[this->actualScene]->reset();
        }
        else
        {
            this->actualScene = this->Scenes[this->actualScene]->getNextScene();
        }

        gameWindow->display();
        
        if (this->actualScene == enumScene::EXIT) gameWindow->close();
    }

}


