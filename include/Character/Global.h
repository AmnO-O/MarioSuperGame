#pragma once
#include "raylib.h"
#include <string>
#include <memory>
#include <utility>
#include <string>
#include <map>
#include <unordered_map>
#include <filesystem>

class Images {
public: 
	static std::unordered_map <std::string, Texture2D> textures;
	static void loadAllTextures(const std::string& folderPath);
	static void unloadAllTextures(); 
};

enum class ShapeState{
    SMALL, BIG, FIRE, TRANSFORMED
}; 

enum class MoveState{
    STAND, SKID, RUN, JUMP, CROUCH
}; 

enum class CharacterType{
    MARIO, LUIGI
}; 

enum class PowerUpType {
	MUSHROOM,
	FIRE_FLOWER,
	STAR
};

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
	LuigiStats() : CharacterStats(180.0f, -480.0f, -900.0f, 0.4f) {
		runSpeed = 180.0f;          
		jumpInitialVelocity = -480.0f;  
		jumpHoldAcceleration = -900.0f;
		maxJumpTime = 0.4f;
	};
	~LuigiStats() {}; 
};

