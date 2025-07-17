#pragma once
#include "Character/Animation.h"
#include <cassert>
#include "Exceptions.h"

Vector2 SpriteAnimated::getCurrentShape() const{
    assert(currentIndex < frames.size()); 
    
    if (currentIndex < 0 || currentIndex >= frames.size()) 
        throw GameException("Current index out of bounds in SpriteAnimated::getCurrentShape");


    return Vector2({ frames[currentIndex].width, frames[currentIndex].height }); 
}


void SpriteAnimated::update(float deltaTime){

}

void SpriteAnimated::render(){

}