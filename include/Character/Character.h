#pragma once 
#include <fstream>
#include "raylib.h"
#include "Animation.h"
#include "Global.h"
#include "Exceptions.h"
#include "CharacterState.h"
#include "PlayerMovement.h"
#include "Fireball.h"
#include "Observer.h"

class Character : public ICollidable {
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
    void readRectAnimation(const std::string filePath); 
    std::string getShape_Action() const; 
    void shootFireball();
    void cleanFireballs(); 
    void updateShape(); 
    void setup(); 
public: 
    Character(CharacterType type, Vector2 pos); 
    Character(CharacterType type, float cordX, float groundLevel); 

    Vector2 getPosition() const {return movement->getPosition(); }
    Rectangle getHitbox() const override {return hitbox; }
    bool isBig() const { return dynamic_cast<SmallState*>(Sstate) == nullptr; }

    void adaptCollision(ICollidable* other) override;
    void powerUp(PowerUpType type); 
    void setGroundLevel(float groundLevel) {this->groundLevel = groundLevel; movement->setGroundLevel(groundLevel);}
    void setPosition(Vector2 pos);
    void update(float deltaTime); 
    void render(); 
    
    ~Character(); 
}; 