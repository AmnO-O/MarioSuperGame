#pragma once
#include "raylib.h"
#include <memory>
#include <string>
#include "Global.h"

class PlayerMovement{
private:
    Vector2 position; 
    Vector2 velocity; 
    bool facingRight; 
	std::unique_ptr<CharacterStats> stats;
    
    float groundLevel; 
	float currentTime; 

public: 
    PlayerMovement(Vector2 pos, Vector2 vel, std::unique_ptr<CharacterStats> stats_): 
        position(pos), velocity(vel), stats(std::move(stats_)), facingRight(true){}; 

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

    void update(float deltaTime); 
    Vector2 getPosition() const {return position;}
    bool isFacingRight() const {return facingRight; }

}; 