#pragma once 
#include <fstream>
#include "raylib.h"
#include "Animation.h"
#include "Global.h"
#include "Exceptions.h"
#include "CharacterState.h"
#include "PlayerMovement.h"


class Character{
protected: 
    PlayerMovement* movement; 
    IShapeState *Sstate; 
    IMoveState *Mstate; 

    CharacterType type; 
	std::map<std::string, std::unique_ptr<AnimationManager>> animations; 
	AnimationManager *activeAnimation;

    Rectangle hitbox; 

    void updateHitbox(); 
    void readRectAnimation(const std::string filePath); 
    std::string getShape_Action() const; 
public: 
	
    Character(CharacterType type, Vector2 pos); 
    Vector2 getPosition() const {return movement->getPosition(); }
    Rectangle getHitbox() const {return hitbox; }
    
    void transformToTransformed();
    void transformToFire();

    void update(float deltaTime); 
    void render(); 
    
    ~Character(); 
}; 