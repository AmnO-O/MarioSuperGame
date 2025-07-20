#pragma once
#include "raylib.h"
#include <string>

class IShapeState{
public: 
	IShapeState() = default; 
	virtual std::string getShapeState() const = 0; 
	virtual bool isTransformed() const {return false; }
	virtual bool canBreakBrick() const {return false; }
	virtual bool canShootFire() const {return false; }
	virtual ~IShapeState() = default;
};

class SmallState: public IShapeState{
public: 
	std::string getShapeState() const override {return "SMALL";}
}; 
class TransformedState: public IShapeState{
public: 
	bool isTransformed() const override {return true; }
	std::string getShapeState() const override {return "TRANSFORMED";}
}; 

class BigState: public IShapeState{
public: 
	bool canBreakBrick() const override {return true; }
	std::string getShapeState() const override {return "BIG";}
}; 

class FireState: public IShapeState{
public: 
	bool canBreakBrick() const override {return true; }
	bool canShootFire() const override {return true; }
	std::string getShapeState() const override {return "FIRE";}
}; 

struct MoveContext {
    Vector2& position;
    Vector2& velocity;
    Vector2& force;
	bool &facingRight;
	float &groundLevel;  
    float &currentTime;
	bool 	  &isCrouch; 
    bool      isBig;
};


class IMoveState{
	bool isJump = false; 
public: 
	IMoveState() = default; 
	virtual void update(float deltaTime) = 0; 
	virtual IMoveState *update(MoveContext *Data) = 0;
	virtual std::string getMoveState() const = 0;
	void changeIsJump() {isJump ^= 1;}
	virtual bool isJumping() const {return isJump; }
	virtual bool isSliding() const {return false; }
	virtual ~IMoveState() = default;  
};

class StandState: public IMoveState{
public:
	void update(float deltaTime) override; 
	IMoveState *update(MoveContext *Data) override;
	std::string getMoveState() const override {return "STANDING";}
};

class RunState:public IMoveState{
public: 
	void update(float deltaTime) override; 
	IMoveState *update(MoveContext *Data) override;
	std::string getMoveState() const override {return "RUNNING";}
}; 

class SkidState:public IMoveState{
public: 
	void update(float deltaTime) override; 
	IMoveState *update(MoveContext *Data) override;
	std::string getMoveState() const override {return "SKIDDING";}
}; 

class CrouchState : public IMoveState{
public: 
	void update(float deltaTime) override; 
	IMoveState *update(MoveContext *Data) override;
	std::string getMoveState() const override {return "CROUCHING";}
}; 

class JumpState:public IMoveState{
public: 
	void update(float deltaTime) override; 
	IMoveState *update(MoveContext *Data) override;
	bool isJumping() const override {return true;}
	std::string getMoveState() const override {return "JUMPING";}
}; 

class SlideState:public IMoveState{
public: 
	void update(float deltaTime) override; 
	IMoveState *update(MoveContext *Data) override;
	bool isSliding() const override {return true;}
	std::string getMoveState() const override {return "SLIDING";}
}; 