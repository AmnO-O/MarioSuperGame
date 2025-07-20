#include "Character/Fireball.h"
#include <fstream>
#include <cassert>
#include "Exceptions.h"
#include <iostream>

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

    if (position.y >= groundLevel - 1) {
        position.y = groundLevel;
        velocity.y = -velocity.y * bounceDamp;
    }

    if (fabs(velocity.x) < 250.0f) active = false;
}



void Fireball::render(){
    if(activeAnimation == nullptr)
        throw GameException("activeAnimation is null at Fireball::render"); 
        
    activeAnimation -> render(position); 
}