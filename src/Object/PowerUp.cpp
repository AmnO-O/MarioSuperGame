#include "Object/PowerUp.h"
#include "Character/Character.h"
#include "Blocks/Coin.h"
#include "Blocks/Block.h"
#include <iostream>
#include <cmath>

void PowerUp::update(float delta) {
	if (!active) return;
	if (hasSpawned) 
		GameObject::update(delta);
	else {
		ani.Update(delta);
		if (ani.ended()) {
			hasSpawned = true;
			hitbox = ani.getHitBox(); 
			position = {hitbox.x, hitbox.y};
		}
	}
}

void PowerUp::adaptCollision(ICollidable *other) {
	Character* player = dynamic_cast<Character*>(other);
	if (player) {
		applyEffect(player);
		active = false;
		return;
	}
	if (!hasSpawned || !dynamic_cast<Block*>(other) || dynamic_cast<Coin*>(other)) return;

	Rectangle rect = other->getHitbox();

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
		velocity.y = 0.0f;
	}

	hitbox.x = position.x; 
	hitbox.y = position.y; 
}

void PowerUp::render(){
	if (!active) return; 
	if (hasSpawned)
		DrawTextureRec(tex, srcRect, position, WHITE);
	else	
		ani.Draw();
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