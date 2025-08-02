#pragma once
#include "raylib.h"
#include "Animation/Animation.h"
#include <string>
#include "Character/Global.h"
#include "Object/GameObject.h"

class Fireball : public GameObject{
private:
    const float bounceDamp = 0.9f;
    AnimationManager *activeAnimation = nullptr; 
    void readRectAnimation(const std::string filePath); 
public:
    Fireball(Vector2 startPos, bool facingRight) : GameObject(startPos, {0, 0}) {
        velocity.x = facingRight ? 300.0f : -300.0f;
        velocity.y = 0; 
        hitbox = { position.x, position.y, 16, 16 };
        readRectAnimation("assets/animation/fireball.txt"); 
    }

    bool isActive() const {return (active || activeAnimation->isOnePeriodPassed() == false);}

    void updateHitbox(); 
    void explode(); 

    void update(float deltaTime) override; 
    void render() override; 

    ~Fireball(){
        delete activeAnimation; 
    }
};
