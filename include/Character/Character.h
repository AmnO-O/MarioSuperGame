#pragma once 
#include "raylib.h"
#include "Animation.h"
#include "CharacterState.h"
#include "Global.h"

class Character{
protected: 
    Vector2 position; 
    Vector2 velocity; 
    Rectangle hitbox; 
    bool facingRight; 

    CharacterType type; 
	std::unique_ptr<CharacterStats> stats;

    IShapeState *Sstate; 
    IMoveState *Mstate; 


	std::map<std::string, std::unique_ptr<SpriteAnimated>> animations; 
	SpriteAnimated *activeAnimation;

    void updateHixbox(); 
    void readRectAnimation(const std::string filePath); 
    std::string getShape_Action() const; 
public: 
	
    Character(CharacterType type, Vector2 pos); 
    Vector2 getPosition() const {return position; }
    Rectangle getHitbox() const {return hitbox; }
    
    void transformToTransformed();
    void transformToFire();

    void update(float deltaTime); 
    void render(); 
    
    ~Character() {
        delete Sstate; 
        delete Mstate; 
    }
}; 