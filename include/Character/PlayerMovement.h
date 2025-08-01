#pragma once
#include "raylib.h"
#include <memory>
#include <string>
#include "Global.h"
#include "PowerUp.h"
#include "../Observer/ICollidable.h"

class IMoveState; 
class IShapeState; 
class Character; 

class PlayerMovement{
private:
    Vector2 position; 
    Vector2 velocity; 
    Vector2 shape; 
    bool facingRight; 
	std::unique_ptr<CharacterStats> stats;
    
    float groundLevel; 
	float currentTime; 

    float footHeightFactor = 0.2f;    
public: 
    PlayerMovement(Vector2 pos, Vector2 vel, std::unique_ptr<CharacterStats> stats_): 
        position(pos), velocity(vel), stats(std::move(stats_)), facingRight(true), currentTime(0.0f), groundLevel(0.0){
            shape = {12, 14}; 
        }; 

    PlayerMovement(const PlayerMovement& other)
      : position(other.position),
        velocity(other.velocity),
        facingRight(other.facingRight),
        stats(other.stats
              ? std::make_unique<CharacterStats>(*other.stats)
              : nullptr)
    {}

    PlayerMovement& operator=(const PlayerMovement& other) {
        if (this == &other) return *this;
        position    = other.position;
        velocity    = other.velocity;
        facingRight = other.facingRight;
        stats = other.stats
            ? std::make_unique<CharacterStats>(*other.stats)
            : nullptr;
        return *this;
    } 
    void setFootHeightFactor(float factor) {
        footHeightFactor = factor;
    }
    void setOnGround(); 
    void adaptCollision(ICollidable* other, IMoveState *&Mstate, Player *player); 
    void update(float deltaTime, IShapeState *&Sstate, IMoveState  *&Mstate);
    void setGroundLevel(float groundLevel_); 
    void setPosition(const Vector2 &pos) {position = pos;}
    void setShape(const Rectangle &rect) {position.y = position.y + shape.y - rect.height; shape = {rect.width, rect.height};}
    void setShape(const Vector2 &shape_) {position.y = position.y + shape.y - shape_.y; shape = {shape_.x, shape_.y};}

    Vector2 getPosition() const {return position;}
    bool isFacingRight() const {return facingRight; }

}; 