#include "Animation/Animation.h"
#include <cassert>
#include "Exceptions.h"

Vector2 AnimationManager::getCurrentShape() const{
    assert(currentIndex < frames.size()); 
    
    if (currentIndex < 0 || currentIndex >= frames.size()) 
        throw GameException("Current index out of bounds in SpriteAnimated::getCurrentShape");


    return Vector2({ frames[currentIndex].width, frames[currentIndex].height }); 
}

void AnimationManager::addRect(const Rectangle& rect){
    frames.push_back(rect);
}

void AnimationManager::update(float deltaTime){
    currentTime += deltaTime; 

    if(currentTime >= timeSwitch){
        currentTime -= timeSwitch; 
        currentIndex ++;
    }

    if(currentIndex >= frames.size()){
        currentTime = 0.0f, currentIndex = 0, isOnePeriod = true; 
    }
}

void AnimationManager::render(Vector2 position, bool flip){
    if(currentIndex < 0 || currentIndex >= frames.size()){
        throw GameException("Current index out of bounds in SpriteAnimated::render"); 
    }

	Rectangle frameRec = frames[currentIndex];

    flip ^= flipX; 

    assert(sheet.id != 0); 

	if (flip) 
		frameRec.width *= -1;

	DrawTextureRec(sheet, frameRec, position, WHITE);
}

void AnimationManager::Draw(Vector2 position) const {
    if(currentIndex < 0 || currentIndex >= frames.size()){
        throw GameException("Current index out of bounds in SpriteAnimated::render"); 
    }

	Rectangle frameRec = frames[currentIndex];

    assert(sheet.id != 0); 

	DrawTextureRec(sheet, frameRec, position, WHITE);
}