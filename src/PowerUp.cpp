#include "Character/PowerUp.h"
#include "Character/Character.h"
#include <iostream>
#include <cmath>


void PowerUp::adaptCollision(ICollidable* other){
	Rectangle hitBox = other->getHitbox(); 
	adaptCollision(hitBox); 
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
		velocity.y = 0;
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
	
	activeAnimation = new AnimationManager(sheet, 0); 

	while(fin){
		float x, y, w, h; fin >> x >> y >> w >> h; 
		Rectangle rect = {x, y, w, h}; 
		activeAnimation->addRect(rect); 
	}

	fin.close(); 
	
}

void PowerUp::render(){
	if (!active) return; 

	if(activeAnimation){
		activeAnimation->render({hitbox.x, hitbox.y}); 
		return; 
	}

	Texture2D power; 

	switch (type) {
		case PowerUpType::MUSHROOM: power = Images::textures["mushroom.png"];  break;
		case PowerUpType::NORMAL_MUSHROOM: power = Images::textures["1upMushroom.png"]; break;
	}

	if(power.id == 0){
		throw ResourceException("Can't load texture in powerup::render()\n");
	}
	
	DrawTexture(power, (int) hitbox.x, (int) hitbox.y, WHITE);
}

void MushroomPowerUp::applyEffect(Player* &character) {
    if(active == false) return; 
	active = false; 
	character->powerUp(this->type); 
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
}

void StarPowerUp::adaptCollision(const Rectangle &other){
    float penTop    = (hitbox.y + hitbox.height) - other.y;
    float penBottom = (other.y + other.height) - hitbox.y;
    float penLeft   = (hitbox.x + hitbox.width)  - other.x;
    float penRight  = (other.x + other.width)    - hitbox.x;

    float minPen = penTop;
    Vector2 normal = { 0, +1 };  
    if (penBottom < minPen) {
        minPen = penBottom;
        normal = { 0, -1 };     
    }
    if (penLeft < minPen) {
        minPen = penLeft;
        normal = { +1, 0 };     
    }
    if (penRight < minPen) {
        minPen = penRight;
        normal = { -1, 0 };     
    }

    position.x += normal.x * minPen;
    position.y += normal.y * minPen;
	
	hitbox = { position.x, position.y, hitbox.width, hitbox.height };

    velocity = reflect(velocity, normal);

    if (std::fabs(normal.y) > 0.5f) {
        velocity.y = -std::sqrt(2.0f * 980.0f * h_bounce);
    } else {
        velocity = reflect(velocity, normal);
    }
}

void StarPowerUp::update(float deltaTime){
	PowerUp::update(deltaTime); 

	if (position.y >= groundLevel) {
        position.y = groundLevel;    
		hitbox = { position.x, position.y, hitbox.width, hitbox.height };

        Rectangle groundRect = { -1e6f, groundLevel, 2e6f, 1.0f };
        adaptCollision(groundRect);
    }
}
