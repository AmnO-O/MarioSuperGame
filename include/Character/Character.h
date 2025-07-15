#pragma once 
#include "raylib.h"
#include "Animation.h"
#include "CharacterState.h"
#include <memory>
#include <string>

class CharacterStats {
public: 
	float runSpeed; 
	float jumpInitialVelocity; 
	float jumpHoldAcceleration; 
	float maxJumpTime; 
public: 
	CharacterStats(float speed, float jumpIV, float jumpHold, float maxJT)
		:runSpeed(speed), jumpInitialVelocity(jumpIV), jumpHoldAcceleration(jumpHold), maxJumpTime(maxJT) {};
	virtual ~CharacterStats() = default; 
};

class MarioStats : public CharacterStats {
public: 
	MarioStats() : CharacterStats(300.0f, -10000.0f, -1300.0f, 0.25f) {
		runSpeed = 300.0f, jumpInitialVelocity = -10000.0f, jumpHoldAcceleration = -1300.0f, maxJumpTime = 0.25f; ;
	};

	~MarioStats() {}; 
};

class LuigiStats : public CharacterStats {
public: 
	LuigiStats() : CharacterStats(180.0, -480.0, -900.0, 0.4) {
		runSpeed = 180.0f;          
		jumpInitialVelocity = -480.0f;  
		jumpHoldAcceleration = -900.0f;
		maxJumpTime = 0.4f;
	};
	~LuigiStats() {}; 
};


class Character{
protected: 
    Vector2 position; 
    Vector2 velocity; 
    Rectangle hitbox; 

    ShapeState Sstate; 
    MoveState Mstate; 

    CharacterType type; 
	std::unique_ptr<CharacterStats> stats;

    bool facingRight; 
    void updateHixbox(); 
    void readRectAnimation(const std::string filePath); 
    
public: 
	Character(CharacterType type, Vector2 pos); 
    Vector2 getPosition() const {return position; }
    Rectangle getHitbox() const {return hitbox; }

    void update(float deltaTime); 
    void render(); 
}; 