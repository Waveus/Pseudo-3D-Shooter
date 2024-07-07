#pragma once
#include "entity.h"
class dummy : public entity
{
private:
	sf::Sprite dummy3DSprite;
public:
	dummy(int size, int meshSpacing, int speedIni, int hpIni, sf::Vector2f playerSpawn, const sf::Texture* texture2DIni, std::shared_ptr<sf::Texture> texture3DIni) : entity(size, speedIni, hpIni, playerSpawn) {
		this->entityBody.setTexture(texture2DIni);
		this->dummy3DSprite.setTexture(*texture3DIni);
		this->moveDirectionBasedEntityRotation = sf::Vector2f(0, 0);
		this->entityBody.move(meshSpacing / 2, meshSpacing / 2);
		this->hitbox.move(meshSpacing / 2, meshSpacing / 2);
	};

	sf::Sprite& get3DSprite();
	sf::Sprite get3DSpriteCopy();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(this->entityBody, states);
	}
};

