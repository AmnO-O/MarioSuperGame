#pragma once
#include "raylib.h"

class GameObject{
protected: 
    Vector2 position; 
    Vector2 velocity; 
    Rectangle hitbox; 
    float groundLevel; 
    bool active; 
public: 
    GameObject(Vector2 pos, Vector2 vel): position(pos), velocity(vel), groundLevel(0.0f), active(true){} 

    Rectangle getHitbox() const {return hitbox;}
    Vector2 getPosition() const {return position;}

    virtual void setGroundLevel(float groundLevel) {this->groundLevel = groundLevel;}

    virtual void update(float deltaTime){
        if(active == false) return ; 

        velocity.y += 980 * deltaTime; 
        position.x += velocity.x * deltaTime; 
        position.y += velocity.y * deltaTime; 

        hitbox.x = position.x;
        hitbox.y = position.y;
    }

    virtual void render() = 0; 
}; 