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
    if(active == false){ 
        return; 
    }
    
    delete activeAnimation; 

    active = false; 
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


void Fireball::adaptCollision(const Rectangle &rect) {
	float penLeft = (position.x + hitbox.width) - rect.x; 
	float penRight = (rect.x + rect.width) - position.x;
	float penX = penLeft < penRight ? -penLeft : penRight; 

	float penTop = (position.y + hitbox.height) - rect.y;
	float penBot = (rect.y + rect.height) - position.y;
	float penY = penTop < penBot ? -penTop : penBot;

    float minPen = penTop;
    Vector2 normal = { 0, +1 };  

    if (penBot < minPen) {
        minPen = penBot;
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
    
	
    velocity = reflect(velocity, normal);

    if (std::fabs(normal.y) > 0) {
        velocity.y = -std::sqrt(2.0f * 980.0f * h_bounce);
    }else
        velocity = reflect(velocity, normal);

    
    if (std::fabs(penX) < std::fabs(penY)) {
        explode();
    }
	else if (penY < 0) 
        Fireball::setGroundLevel(rect.y);


    updateHitbox(); 
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

    if (position.y >= groundLevel - hitbox.height) {
        Rectangle groundRect = { -1e6f, groundLevel, 2e6f, 1.0f };

        adaptCollision(groundRect);
    }

    updateHitbox(); 
}


void Fireball::updateHitbox(){

    hitbox.x = position.x; 
    hitbox.y = position.y; 
    hitbox.height = 9.0f; 
    hitbox.width = 8.0f;

}


void Fireball::render(){
    if(activeAnimation == nullptr)
        throw GameException("activeAnimation is null at Fireball::render"); 

    activeAnimation -> render(position); 
}