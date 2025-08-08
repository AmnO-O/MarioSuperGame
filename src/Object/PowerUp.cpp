#include "Object/PowerUp.h"
#include "Character/Character.h"
#include "Blocks/Coin.h"
#include "Blocks/Block.h"
#include <iostream>
#include <cmath>

void PowerUp::update(float delta) {
	if (!active) return;
	if (hasSpawned) {
		GameObject::update(delta);
		activeAnimation->update(delta);
	}
	else {
		ani->Update(delta);
		if (ani->ended()) {
			hasSpawned = true;
			hitbox = ani->getHitBox(); 
			position = {hitbox.x, hitbox.y};
		}
	}
}

void PowerUp::adaptCollision(ICollidable *other) {
	Player* player = dynamic_cast<Player*>(other);
	if (player) {
		applyEffect(player);
		active = false;
		return;
	}
	if (!hasSpawned || !dynamic_cast<Block*>(other) || dynamic_cast<Coin*>(other)) return;

	Rectangle rect = other->getHitbox();
	adaptCollision(rect); 
}

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
		velocity.y = 0.0f;
		if(penY < 0){
			setGroundLevel(rect.y);
		}
	}

	hitbox.x = position.x; 
	hitbox.y = position.y; 
}


void PowerUp::readRectAnimation(std::string filePath, Texture2D &sheet){
	std::ifstream fin(filePath); 

	if(!fin)
		throw ResourceException("Can't load file " + filePath + " in PowerUp::readRect"); 

	if(sheet.id == 0){
		throw ResourceException("Can't load sheet in PowerUp::readRect"); 
	}
	
	activeAnimation = new AnimationManager(sheet, 0, 0.2f); 

	while(fin){
		float x, y, w, h; fin >> x >> y >> w >> h; 
		Rectangle rect = {x, y, w, h}; 
		activeAnimation->addRect(rect); 
		if (!ani)
			ani = new AppearanceAnimation(sheet, {0, 0, 0, 0}, 0.8f, h, 0.2f);
		ani->addRect(rect);
	}

	fin.close(); 
	
}

void PowerUp::render(){
	if (!active) return; 
	if (hasSpawned) {
		if(activeAnimation){
			activeAnimation->render({hitbox.x, hitbox.y}, (velocity.x < 0)); 
			return; 
		}
	}
	else	
		ani->Draw();
}

void MushroomPowerUp::applyEffect(Player* &character) {
    if(active == false) return; 
	active = false; 
	character->powerUp(this->type);
	PlaySound(SoundManager::getInstance().mushroomSound); 
}

void MushroomPowerUp::update(float deltaTime){
	PowerUp::update(deltaTime); 

	if(position.y >= groundLevel - 16){
		position.y = groundLevel - 16; 
		velocity.y = 0; 
	}
	
	hitbox = { position.x, position.y, hitbox.width, hitbox.height };
}


void NormalMushroomPowerUp::update(float deltaTime){
	PowerUp::update(deltaTime); 

	if(position.y >= groundLevel - 16){
		position.y = groundLevel - 16; 
		velocity.y = 0; 
	}
	hitbox = { position.x, position.y, hitbox.width, hitbox.height };
}

void NormalMushroomPowerUp::applyEffect(Player* &character){
    if(active == false) return; 

	active = false; 
}

void FireFlowerPowerUp::applyEffect(Player* &character) {
    if(active == false) return; 

	active = false;
	character->powerUp(this->type);
	PlaySound(SoundManager::getInstance().mushroomSound);
}

void FireFlowerPowerUp::update(float deltaTime) {
	PowerUp::update(deltaTime); 

	velocity.y = 0; 
	position.y = groundLevel - 16.0f; 
	hitbox = { position.x, position.y, hitbox.width, hitbox.height };
}


void StarPowerUp::applyEffect(Player* &character) {
    if(active == false) return; 

	active = false;
	character->powerUp(this->type);
	PlaySound(SoundManager::getInstance().mushroomSound);
}

void StarPowerUp::adaptCollision(const Rectangle &rect) {
    float penLeft = (position.x + hitbox.width) - rect.x; 
    float penRight = (rect.x + rect.width) - position.x;
    float penTop = (position.y + hitbox.height) - rect.y;
    float penBot = (rect.y + rect.height) - position.y;

    float minPen = std::min({penLeft, penRight, penTop, penBot});

    Vector2 normal = {0, 0};
    if (minPen == penLeft) {
        normal = {-1, 0};
    } else if (minPen == penRight) {
        normal = {1, 0}; 
    } else if (minPen == penTop) {
        normal = {0, -1};
    } else if (minPen == penBot) {
        normal = {0, 1}; 
	}
	
    position.x += normal.x * minPen;
    position.y += normal.y * minPen;

    if (normal.y != 0) {
        if(normal.y < 0) velocity.y = -std::sqrt(2.0f * 980.0f * h_bounce);
		if(normal.y < 0) setGroundLevel(rect.y);
    } else if (normal.x != 0) {
        velocity.x *= -1;
    }

    hitbox = {position.x, position.y, hitbox.width, hitbox.height};
}

void StarPowerUp::update(float deltaTime){
	PowerUp::update(deltaTime); 

	if (position.y >= groundLevel - hitbox.height) {
        position.y = groundLevel - hitbox.height;    
		hitbox = { position.x, position.y, hitbox.width, hitbox.height };

        Rectangle groundRect = { -1e6f, groundLevel, 2e6f, 1.0f };
        adaptCollision(groundRect);
    }
}
