#pragma once
#include "raylib.h"
#include <memory>
#include <string>
#include "Global.h"
#include "Object/PowerUp.h"
#include "Observer/ICollidable.h"

class IMoveState; 
class IShapeState; 
class Character; 

class LerpMover{
private:
    Vector2 startPos;
    Vector2 endPos;
    float   duration = 2.0f;    
    float   elapsed = 0;   
    bool    active  = false;
public: 
    void start(const Vector2& from, const Vector2& to, float timeSeconds) {
        startPos = from;
        endPos   = to;
        duration = timeSeconds > 0 ? timeSeconds : 0.001f;
        elapsed  = 0;
        active   = true;
    }

    Vector2 update(float dt) {
        if (!active) return endPos;

        elapsed += dt;
        float t = elapsed / duration;
        if (t >= 1.0f) {
            t      = 1.0f;
            active = false;
        }

        return {
            startPos.x + t * (endPos.x - startPos.x),
            startPos.y + t * (endPos.y - startPos.y)
        };
    }

    bool isDone() const { return !active; }
}; 

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


    bool isDoneLerpMoving() const {return lerpMover.isDone();}

    void setVelocityY(float velocityY) {velocity.y = velocityY;}
    void setVelocityX(float velocityX) {velocity.x = velocityX;}
    void setOnGround(); 

    void setGroundLevel(float groundLevel_); 
    void setPosition(const Vector2 &pos) {position = pos;}

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