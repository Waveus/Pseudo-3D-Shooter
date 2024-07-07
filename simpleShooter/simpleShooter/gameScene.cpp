#include "gameScene.h"

gameScene::gameScene(std::shared_ptr<sf::RenderTarget> rendererIni, std::shared_ptr<ResourceManager> resourceManIni, std::shared_ptr<std::string> selectedMapIni, std::shared_ptr<betterCounter> difficultyIni)
{
	this->renderer = rendererIni;
	this->resourceMan = resourceManIni;
	this->selectedMap = selectedMapIni;
	this->myMesh = std::make_shared<Mesh>(40.f / 1920.f * (float)SCREENWIDTH);

	this->Textures = this->resourceMan->getTexturesBySet("Map");
	this->Fonts = this->resourceMan->getFonts();
	this->Maps = this->resourceMan->getMaps();
	this->difficulty = difficultyIni;

	this->nextScene = enumScene::GAME;
	pistolAnimation.push_back(this->Textures["pistol0"]);
	pistolAnimation.push_back(this->Textures["pistol1"]);
	pistolAnimation.push_back(this->Textures["pistol2"]);
	pistolAnimation.push_back(this->Textures["pistol3"]);
	pistolAnimation.push_back(this->Textures["pistol4"]);
	pistolAnimation.push_back(this->Textures["pistol5"]);
	pistolAnimation.push_back(this->Textures["pistol6"]);
	pistolAnimation.push_back(this->Textures["pistol7"]);
}

void gameScene::handleKeyboard()
{
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		this->nextScene = enumScene::MENU;
	}

	this->myPlayer->keyboardHandler();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{

		if(this->myPlayer->triggerGun())
		{
			this->animationCounter = 0;
			this->activeBullets->addToList(myPlayer->getBullet());
		}
	}
}

void gameScene::render2D()
{

	this->renderer->draw(*myMap);
	this->renderer->draw(*myMesh);
	this->renderer->draw(*myPlayer);

	this->renderer->draw(*activeBullets);
	this->renderer->draw(*aliveDummies);
	this->renderer->draw(*myRaycasting);
}

void gameScene::render3D()
{
	std::map<float, std::vector<std::shared_ptr<sf::Drawable>>> whatToDrawFirst;
	int positionOfVerticalStripe = 0;

	//drawing floor 
	for (float i = SCREENHEIGHT / 2; i < SCREENHEIGHT; i += 4)
	{
		sf::RectangleShape floor(sf::Vector2f(SCREENWIDTH, 4));
		floor.setFillColor(sf::Color(60.f - (40.f * i / (float)SCREENHEIGHT), 60.f - (40.f * i / (float)SCREENHEIGHT), 60.f - 40.f * (i / SCREENHEIGHT)));
		floor.setPosition(0, SCREENHEIGHT - positionOfVerticalStripe);
		positionOfVerticalStripe+=4;
		this->renderer->draw(floor);
	}

	//drawing sky
	sf::RectangleShape sky(sf::Vector2f(SCREENWIDTH, SCREENHEIGHT / 2));
	sky.setPosition(0, 0);
	sky.setFillColor(sf::Color(25, 107, 166));
	this->renderer->draw(sky);

	/////////////////////////////////

	//drawing stripes of textures for every ray that fit 
	int i = 0;
	sf::Vector2f playerCentre = this->myPlayer->getHitbox().getPosition();
	for (auto& ray : this->myRaycasting->getRays())
	{
		float getRidOfFishEye = cos(std::abs(this->myPlayer->getEntity().getRotation() - ray->getBody().getRotation()) / 180.f * M_PI);

		sf::Vector2f rayPos = ray->getBody().getPosition();
		float rayDistancePlayerWall = std::sqrt((rayPos.x - playerCentre.x) * (rayPos.x - playerCentre.x) + (rayPos.y - playerCentre.y) * (rayPos.y - playerCentre.y)) * getRidOfFishEye;
		sf::RectangleShape shape(sf::Vector2f(1, ((this->myPlayer->getHitbox().getSize().x * 2)  *  SCREENHEIGHT / rayDistancePlayerWall)));

		sf::Vector2i wallBuffer = ray->getActualSquare();
		int stripe;

		if (ray->getHitVertically())
		{
			stripe = ray->getBody().getPosition().y - wallBuffer.y;
		}
		else 
		{
			stripe = ray->getBody().getPosition().x - wallBuffer.x;
		}
		shape.setTexture(this->Textures[myMap->getWallTexture(wallBuffer.x, wallBuffer.y)].get());
		shape.setTextureRect(sf::IntRect(stripe, 0, 1, 40));

		shape.setPosition(i, (SCREENHEIGHT - shape.getSize().y) / 2);
		i++;

		whatToDrawFirst[-rayDistancePlayerWall].push_back(std::make_shared<sf::RectangleShape>(shape));

		//this->renderer->draw(shape);
	}



	for (auto& dummy : this->aliveDummies->getDummyList())
	{
		

		sf::Vector2f dummyPosition = dummy->getHitbox().getPosition();
		sf::Vector2f rotationVectorPlayer = { (float)cos(this->myPlayer->getEntity().getRotation() / 180.f * M_PI), (float)sin(this->myPlayer->getEntity().getRotation() / 180.f * M_PI) };
		sf::Vector2f vectorplayerDummy = { dummyPosition.x - playerCentre.x, dummyPosition.y - playerCentre.y };


		float angleRelative = acos((vectorplayerDummy.x * rotationVectorPlayer.x + vectorplayerDummy.y * rotationVectorPlayer.y) / (std::sqrt(vectorplayerDummy.x * vectorplayerDummy.x + vectorplayerDummy.y * vectorplayerDummy.y) * std::sqrt(rotationVectorPlayer.x * rotationVectorPlayer.x + rotationVectorPlayer.y * rotationVectorPlayer.y)));
		float leftRightValue = rotationVectorPlayer.x * vectorplayerDummy.y - rotationVectorPlayer.y * vectorplayerDummy.x;
		
		float angleRelativedeg = angleRelative / M_PI * 180.f;

		int right;

		if (leftRightValue > 0) right = 1;
		else right = -1;


		float distancePlayerDummy = std::sqrt((dummyPosition.x - playerCentre.x) * (dummyPosition.x - playerCentre.x) + (dummyPosition.y - playerCentre.y) * (dummyPosition.y - playerCentre.y));
		dummy->get3DSprite().setScale(SCREENHEIGHT / distancePlayerDummy, SCREENHEIGHT / distancePlayerDummy);
		dummy->get3DSprite().setPosition(SCREENWIDTH *0.5f + right *(angleRelativedeg / (66.f * 0.5f)) * SCREENWIDTH *0.5f, (SCREENHEIGHT - dummy->get3DSprite().getGlobalBounds().getSize().y) / 2 + 10 / 1920.f * (float)SCREENWIDTH);
		dummy->get3DSprite().move(-dummy->get3DSprite().getGlobalBounds().width/2, 0);

		whatToDrawFirst[-distancePlayerDummy].push_back(std::make_shared<sf::Sprite>(dummy->get3DSprite()));
	}

	for (auto& i : whatToDrawFirst)
	{
		for (auto& j : i.second)
		{
			this->renderer->draw(*j);
		}
	}

	if (this->animationCounter < 7) animationCounter++;
	sf::Sprite pistol(*this->pistolAnimation[animationCounter]);
	pistol.setScale(5, 5);
	pistol.setPosition(1000, 500);
	this->renderer->draw(pistol);

	sf::RectangleShape crosshair(sf::Vector2f(4, 4));
	crosshair.setFillColor(sf::Color::Magenta);
	crosshair.setPosition(((SCREENWIDTH - crosshair.getGlobalBounds().width) * 0.5f), (SCREENHEIGHT - crosshair.getGlobalBounds().height) * 0.5f);
	this->renderer->draw(crosshair);
}

void gameScene::reset()
{
	this->activeBullets = std::make_unique<allActiveBullets>();
	this->aliveDummies = std::make_unique<activeDummies>();
	this->myRaycasting = std::make_unique<Raycasting>(5.f / 1920.f * (float)SCREENWIDTH, 66.f, this->myMesh->getSpacing(), sf::Color(200,0,50)); //raysize, FOVIni, meshSpacing, ColorOfRays

	this->myMap = std::make_shared<realMap>(this->Maps[*this->selectedMap], this->myMesh->getSpacing());
	this->myPlayer = std::make_shared<player>(12 / 1920.f * (float)SCREENWIDTH, this->myMesh->getSpacing(), 2 / 1920.f * (float)SCREENWIDTH, 10, this->myMap->getSpawnPosition(), this->Textures["circleTexture"].get()); //speed 2, hp 10

	for (auto position : this->myMap->getDummies())
	{
		this->aliveDummies->addDummy(std::make_unique<dummy>(8 / 1920.f * (float)SCREENWIDTH, this->myMesh->getSpacing(), 0, 20 * this->difficulty->getinnerCounter(), position.getPosition(), this->Textures["dummyTexture"].get(), this->Textures["dummy3D"])); //size, spacing, speed, hp etc.
	}
	
	this->myCollisionHandler = std::make_unique<collisionHandler>(this->myPlayer, this->myMap);
	this->activeBullets = std::make_unique<allActiveBullets>();
	this->animationCounter = 7;
}

void gameScene::run()
{
	this->nextScene = enumScene::GAME;
	this->handleKeyboard();
	this->activeBullets->moveBullets();

	//Raycasting
	
	this->myRaycasting->castRays(this->myPlayer->getEntity().getPosition(), this->myPlayer->getEntity().getRotation());
	this->myRaycasting->InitPos();

	//Raycasting END
	

	this->myCollisionHandler->passRaycasting(std::move(this->myRaycasting));
	this->myCollisionHandler->passBullets(std::move(this->activeBullets));
	this->myCollisionHandler->passDummies(std::move(this->aliveDummies));

	this->myCollisionHandler->handleCollisions();
	this->myRaycasting = this->myCollisionHandler->returnRaycasting();
	this->activeBullets = this->myCollisionHandler->returnBullets();
	this->aliveDummies = this->myCollisionHandler->returnDummies();


	this->render3D();
	//this->render2D();

	if (this->aliveDummies->getDummyList().size() == 0) this->nextScene = enumScene::MENU;
}

enumScene gameScene::getNextScene()
{
	return this->nextScene;
}
