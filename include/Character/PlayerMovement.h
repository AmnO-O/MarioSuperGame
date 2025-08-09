#pragma once
#include "raylib.h"
#include <memory>
#include <string>
#include "Global.h"
#include "Object/PowerUp.h"
#include "Observer/ICollidable.h"
#include "Animation/LerpMover.h"

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
    LerpMover lerpMover; 

    float groundLevel; 
	float currentTime; 

    bool disableUpdate = false; 
    bool disableInput = false; 

public: 
    PlayerMovement(Vector2 pos, Vector2 vel, std::unique_ptr<CharacterStats> stats_): 
        position(pos), velocity(vel), stats(std::move(stats_)), facingRight(true), currentTime(0.0f), groundLevel(0.0), disableUpdate(false){
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

    void lockMovement(){disableUpdate  = true;}
    void unlockMovement() {disableUpdate = false;}
    bool isLocked() const { return disableUpdate; }

    void lockKeyboardInput(){disableInput = true;}
    void unlockKeyboardInput(){disableInput = false;}
    bool isLockedKeyboardInput() const {return disableInput;}

    bool isDoneLerpMoving() const {return lerpMover.isDone();}

    void setOnGround(); 
    void setGroundLevel(float groundLevel_); 
    void setPosition(const Vector2 &pos) {position = pos;}
    
    void setFacingRight(bool facingRight_) {facingRight = facingRight_;}
    void setVelocityY(float velocityY) {velocity.y = velocityY;}
    void setVelocityX(float velocityX) {velocity.x = velocityX;}

    void setShape(const Rectangle &rect) {position.y = position.y + shape.y - rect.height; shape = {rect.width, rect.height};}
    void setShape(const Vector2 &shape_) {position.y = position.y + shape.y - shape_.y; shape = {shape_.x, shape_.y};}

    void adaptCollision(ICollidable* other, IMoveState *&Mstate, Player *player); 
    bool adapt_collision_with_enimies(ICollidable* other, Player *player); 
    void update(float deltaTime, IShapeState *&Sstate, IMoveState  *&Mstate);


    void run_from_a_to_b(float startX, float endX){
        if(lerpMover.isDone()){
            lerpMover.start({startX, position.y}, {endX, position.y}, 2.0f); 
        }
    }


    Vector2 getPosition() const {return position;}
    bool isFacingRight() const {return facingRight; }

}; 