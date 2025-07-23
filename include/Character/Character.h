#pragma once 
#include <fstream>
#include "raylib.h"
#include "Animation.h"
#include "Global.h"
#include "Exceptions.h"
#include "CharacterState.h"
#include "PlayerMovement.h"
#include "Fireball.h"

class Character{
private: 
    PlayerMovement* movement; 
    IShapeState *Sstate; 
    IMoveState *Mstate; 

    CharacterType type; 
	std::map<std::string, std::unique_ptr<AnimationManager>> animations; 
    std::vector<Fireball*> fireballs;
	AnimationManager *activeAnimation;

    Rectangle hitbox; 
    float groundLevel; 

    void updateHitbox(); 
    void readRectAnimation(const std::string filePath, Texture2D &sheet); 
    std::string getShape_Action() const; 
    void shootFireball();
    void cleanFireballs(); 
    void updateShape(); 
    void setUp(); 
    void adaptChangePosition(); 
    void animationTransform(); 
public: 
    Character(CharacterType type, Vector2 pos); 
    Character(CharacterType type, float cordX, float groundLevel); 

    Vector2 getPosition() const {return movement->getPosition(); }
    void setPosition(const Vector2 &pos); 
    Rectangle getHitbox() const {return hitbox; }

    void adaptCollision(const Rectangle& rect);
    void powerUp(PowerUpType type); 
    void setGroundLevel(float groundLevel); 
    void update(float deltaTime); 
    void render(); 
    
    ~Character(); 
}; 