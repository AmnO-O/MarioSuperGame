#pragma once
#include "raylib.h"
#include "Animation.h"
#include <string>
#include "Global.h"

class Fireball {
private:
    Vector2 position;
    Vector2 velocity;
    Rectangle hitbox;
    float groundLevel; 
    bool active;
    const float bounceDamp = 0.7f;

    AnimationManager *activeAnimation = nullptr; 
    void readRectAnimation(const std::string filePath); 
public:
    Fireball(Vector2 startPos, bool facingRight) : position(startPos), active(true) {
        velocity.x = facingRight ? 300 : -300;
        velocity.y = 0; 
        hitbox = { position.x, position.y, 16, 16 };
        readRectAnimation("assets/animation/fireball.txt"); 
    }

    Rectangle getHitbox() const {return hitbox;}
    Vector2 getPosition() const {return position;}
    void setGroundLevel(float groundLevel)  {this->groundLevel = groundLevel;}; 
    bool isActive() const {return (active || activeAnimation->isOnePeriodPassed() == false);}
    void explode(); 
    void update(float deltaTime); 
    void render(); 

    ~Fireball(){
        delete activeAnimation; 
    }
};
