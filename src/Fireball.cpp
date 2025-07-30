#include "Character/Fireball.h"
#include <fstream>
#include <cassert>
#include "Exceptions.h"
#include <iostream>
#include <cmath>

void Fireball::readRectAnimation(const std::string filePath){
    std::ifstream fin(filePath); 

    activeAnimation = new AnimationManager(Images::textures["enemies1.png"], 0);

    if(Images::textures["enemies1.png"].id == 0)
		throw GameException("Can't load image of mario.png");

    for(int i = 0; i < 4; i ++){
        int x, y, width, height; 
        fin >> x >> y >> width >> height; 
        activeAnimation -> addRect(Rectangle({ x * 1.0f, y * 1.0f, width * 1.0f, height*1.0f }));
    }

    fin.close(); 
}

void Fireball::explode(){
    delete activeAnimation; 
    
    std::ifstream fin("assets/animation/fireball_explode.txt"); 
    activeAnimation = new AnimationManager(Images::textures["enemies_sprites.png"], 0);

    if(Images::textures["enemies_sprites.png"].id == 0)
		throw GameException("Can't load image of mario.png");

    for(int i = 0; i < 3; i ++){
        int x, y, width, height; 
        fin >> x >> y >> width >> height; 
        activeAnimation -> addRect(Rectangle({ x * 1.0f, y * 1.0f, width * 1.0f, height*1.0f }));
    }

    fin.close(); 


}


void Fireball::adaptCollision(const Rectangle &other){
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

void Fireball::adaptCollision(ICollidable *other){
    adaptCollision(other->getHitbox()); 
}

void Fireball::update(float deltaTime){
    if(active == false){
        if(activeAnimation -> isOnePeriodPassed() == false){
            activeAnimation -> update(deltaTime); 
        }

        return; 
    }

    activeAnimation -> update(deltaTime); 

    velocity.y += 980 * deltaTime;

    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;

	if (position.y >= groundLevel) {
        position.y = groundLevel;    
		hitbox = { position.x, position.y, hitbox.width, hitbox.height };

        Rectangle groundRect = { -1e6f, groundLevel, 2e6f, 1.0f };
        adaptCollision(groundRect);
    }

    updateHitbox(); 
}


void Fireball::updateHitbox(){
    
}


void Fireball::render(){
    if(activeAnimation == nullptr)
        throw GameException("activeAnimation is null at Fireball::render"); 
        
    activeAnimation -> render(position); 
}