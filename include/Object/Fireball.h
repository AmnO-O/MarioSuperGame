#pragma once
#include "raylib.h"
#include "Animation/Animation.h"
#include <string>
#include "Character/Global.h"
#include "Object/GameObject.h"
#include "Observer/ICollidable.h"
#include <iostream>

class Fireball : public GameObject, public ICollidable{
private:
    AnimationManager *activeAnimation = nullptr; 
    void readRectAnimation(const std::string filePath); 

    const float bounceDamp = 0.4f;
    const float e = 1.0f;
    const float h_bounce = 20.0f;

    Vector2 reflect(const Vector2& v, const Vector2& n) {
        float dot = v.x*n.x + v.y*n.y;

        return { v.x - (1 + e) * dot * n.x,
                v.y - (1 + e) * dot * n.y };
    }

public:
    std::string getTypeID() const override { return "FIREBALL"; }

    void printData(std::ostream &fout) const override {
        GameObject::printData(fout);
    }

    void loadData(std::istream &fin) override {
        GameObject::loadData(fin);
    }

    Fireball(Vector2 startPos, bool facingRight) : GameObject(startPos, {0, 0}) {
        velocity.x = facingRight ? 170.0f : -170.0f;
        velocity.y = 0; 
        hitbox = { position.x, position.y, 16, 16 };
        readRectAnimation("assets/animation/fireball.txt"); 
        activeAnimation->setTimeSwitch(0.08f);
    }

    bool isActive() const {return (active || activeAnimation->isOnePeriodPassed() == false);}
    
    Rectangle getHitbox() const override {
        return GameObject::getHitbox();
    }

    void setGroundLevel(float groundLevel) override {
        this->groundLevel = groundLevel;
    
        if(position.y >= groundLevel - 16){
            position.y = groundLevel - 16;    
        }
    }


    void updateHitbox(); 
    void explode(); 


    void adaptCollision(ICollidable* other) override; 
    void adaptCollision(const Rectangle &rect); 

    void update(float deltaTime) override; 
    void render() override; 

    ~Fireball(){
        delete activeAnimation; 
    }
};
