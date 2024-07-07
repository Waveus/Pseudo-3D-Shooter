#include "mapSelectScene.h"


mapSelectScene::mapSelectScene(std::shared_ptr<sf::RenderTarget> rendererIni, std::shared_ptr<ResourceManager> resourceManIni, std::shared_ptr<std::string> selectedMapIni)
{
    this->selectedMap = selectedMapIni;
    this->renderer = rendererIni;
    this->resourceMan = resourceManIni;
    this->Maps = this->resourceMan->getMaps();
    this->Fonts = this->resourceMan->getFonts();
    this->Textures = this->resourceMan->getTexturesBySet("MapSelector");
    this->clickedBefore = true;

    this->title = sf::Sprite(*this->Textures["title"]);
    title.setOrigin(sf::Vector2f(title.getGlobalBounds().width / 2, title.getGlobalBounds().height / 2));
    title.move(sf::Vector2f(SCREENWIDTH / 2, SCREENHEIGHT / 4));


    for (auto& map : Maps)
    {
        std::cout << map.first << std::endl;
        for (auto& a : map.second)
        {
            std::cout << a << std::endl;
        }
    }
   
    selector = std::make_unique<buttonSelectHandler>(SCREENHEIGHT / 3, 70);

    for (auto& map : Maps)
    {
        this->selector->add(std::make_shared<betterButton>(this->Fonts["editundo"], map.first));
    }
    this->selector->add(std::make_shared<betterButton>(this->Fonts["editundo"], "BACK"));

    this->selector->check();
}

enumScene mapSelectScene::getNextScene()
{

    return this->nextScene;
}

void mapSelectScene::reset()
{
    this->selector->previous();
    this->selector->previous();
    this->selector->previous();
}

void mapSelectScene::run()
{
    this->nextScene = enumScene::SELECTMAP;
    this->render();
    this->handleKeyboard();
}

void mapSelectScene::handleKeyboard()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        if (not clickedBefore)
        {
            this->selector->previous();
            clickedBefore = true;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        if (not clickedBefore)
        {
            this->selector->next();
            clickedBefore = true;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        if (not clickedBefore)
        {
            if (this->selector->getSelectedButtonText() == "BACK")
            {
                this->nextScene = enumScene::MENU;
            }
            else
            {
                this->nextScene = enumScene::GAME;
                *this->selectedMap = this->selector->getSelectedButtonText();
            }
                clickedBefore = true;
        }
    }
    else
    {
        clickedBefore = false;
    }
}

void mapSelectScene::render()
{
    this->renderer->draw(this->title);

    for (const auto& button : this->selector->get())
    {
        this->renderer->draw(*button);
    }
}
