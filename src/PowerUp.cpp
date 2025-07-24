#include "Character/PowerUp.h"
#include "Character/Character.h"
#include <iostream>
#include <cmath>

void PowerUp::adaptCollision(const Rectangle &rect){
	float penLeft = (hitbox.x + hitbox.width) - rect.x;
	float penRight = (rect.x + rect.width) - hitbox.x;
	float penX = penLeft < penRight ? -penLeft : penRight;

	float penTop = (hitbox.y + hitbox.height) - rect.y;
	float penBot = (rect.y + rect.height) - hitbox.y;
	float penY = penTop < penBot ? -penTop : penBot;

	if (std::fabs(penX) < std::fabs(penY)) {
		position.x += penX;
		velocity.x *= -1; 
	}
	else {
		position.y += penY;
		velocity.y = 0;
	}

	hitbox.x = position.x; 
	hitbox.y = position.y; 
}

void PowerUp::render(){
	if (!active) return; 

	Texture2D power; 

	switch (type) {
	case PowerUpType::MUSHROOM: power = Images::textures["mushroom.png"];  break;
		case PowerUpType::FIRE_FLOWER: power = Images::textures["mushroom.png"]; break;
		case PowerUpType::STAR: power = Images::textures["star.png"]; break;
	}

	if(power.id == 0){
		throw ResourceException("Can't load texture in powerup::render()\n");
	}
	
	DrawTexture(power, (int)hitbox.x, (int)hitbox.y, WHITE);
}

void MushroomPowerUp::applyEffect(Character* &character) {
    if(active == false) return; 
	active = false; 
	character->powerUp(this->type); 
}

void FireFlowerPowerUp::applyEffect(Character* &character) {
    if(active == false) return; 

	active = false;
	character->powerUp(this->type);
}

void StarPowerUp::applyEffect(Character* &character) {
    if(active == false) return; 

	active = false;
	character->powerUp(this->type);
}