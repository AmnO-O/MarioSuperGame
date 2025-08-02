#pragma once
#include "raylib.h"
#include "Animation/Appearance.h"

class GameObject{
protected: 
    Vector2 position; 
    Vector2 velocity; 
    Rectangle hitbox;
    float groundLevel; 
    bool active; 
public: 
    GameObject(): position({0, 0}), velocity({0, 0}), groundLevel(0.0f), active(true) {} 
    GameObject(Vector2 pos, Vector2 vel): position(pos), velocity(vel), groundLevel(0.0f), active(true) {} 

    virtual Rectangle getHitbox() const { return hitbox; }
    Vector2 getPosition() const {return position;}
    virtual bool IsActive() const { return active; } 

    virtual void setGroundLevel(float groundLevel) {this->groundLevel = groundLevel;}

    virtual void update(float deltaTime){
        if(active == false) return ; 

        velocity.y += 980 * deltaTime; 
        
        position.x += velocity.x * deltaTime; 
        position.y += velocity.y * deltaTime; 

        if(position.y >= groundLevel - 16.0f){
            position.y = groundLevel - 16.0f;
            velocity.y = 0.0f; 
        }

        hitbox.x = position.x;
        hitbox.y = position.y;
    }

    virtual void render() = 0; 
}; 