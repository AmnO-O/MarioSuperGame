#pragma once
#include "raylib.h"
#include <string>

class IShapeState{
public: 
	IShapeState() = default; 
	virtual std::string getShapeState() const = 0; 
	virtual bool canBreakBrick() const {return false; }
	virtual bool canShootFire() const {return false; }
	virtual bool isInvincible() const {return false; }
	virtual ~IShapeState() = default;
};

class SmallState: public IShapeState{
public: 
	std::string getShapeState() const override {return "SMALL";}
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


class ShapeStateDecorator : public IShapeState{
protected:
	IShapeState *wrapped;
public: 
    ShapeStateDecorator(IShapeState *base)
        : wrapped(base) {}
    std::string getShapeState() const override {
        return wrapped->getShapeState();
    }
    bool canBreakBrick() const override {
        return wrapped->canBreakBrick();
    }
    bool canShootFire() const override {
        return wrapped->canShootFire();
    }	

	virtual bool isInvincible() const{
		return wrapped->isInvincible(); 
	}

	virtual ~ShapeStateDecorator() { delete wrapped; }
};


class MorphDecorator : public ShapeStateDecorator{
private: 
    float currentTime = 0.0f;
    const float DURATION = 0.8f; 
public:
    MorphDecorator(IShapeState *base)
        : ShapeStateDecorator(base) {}

    IShapeState *update(float deltaTime) {
        currentTime += deltaTime;

		if (currentTime >= DURATION) 
            return new BigState();
			
		return nullptr;
    }

    std::string getShapeState() const override {
        return "MORPHING(" + wrapped->getShapeState() + ")";
    }
};

class InvincibleDecorator : public ShapeStateDecorator{
private:
    float currentTime = 0.0f;
    const float DURATION = 10.0f; 
public:
    InvincibleDecorator(IShapeState *base)
        : ShapeStateDecorator(base) {}

    IShapeState *update(float deltaTime) {
        currentTime += deltaTime;

	if (currentTime >= DURATION) {
			IShapeState* base = wrapped; 
			wrapped = nullptr;           
			return base; 
		}
		return nullptr;
    }

	bool isInvincible() const override{
		return true; 
	}

    std::string getShapeState() const override {
        return "INVINCIBLE_" + wrapped->getShapeState();
    }
};




struct MoveContext {
    Vector2& position;
    Vector2& velocity;
    Vector2& force;
	Vector2& shape; 
	bool &facingRight;
	float &groundLevel;  
    float &currentTime;
	bool 	  &isCrouch; 
    bool      isBig;
};


class IMoveState{
protected:
	bool isJump = false; 
	float currentTime = 0.0f; 
public: 
	IMoveState() = default; 
	virtual void update(float deltaTime) {currentTime += deltaTime;}; 
	virtual IMoveState *update(MoveContext *Data){return this;}
	virtual std::string getMoveState() const = 0;
	void changeIsJump() {isJump ^= 1;}
	virtual bool isJumping() const {return isJump; }
	virtual bool isClimbing() const {return false; }
	virtual ~IMoveState() = default;  
};

class StandState: public IMoveState{
public:
	IMoveState *update(MoveContext *Data) override;
	std::string getMoveState() const override {return "STANDING";}
};

class RunState:public IMoveState{
public: 
	IMoveState *update(MoveContext *Data) override;
	std::string getMoveState() const override {return "RUNNING";}
}; 

class SkidState:public IMoveState{
public: 
	IMoveState *update(MoveContext *Data) override;
	std::string getMoveState() const override {return "SKIDDING";}
}; 

class CrouchState : public IMoveState{
public: 
	IMoveState *update(MoveContext *Data) override;
	std::string getMoveState() const override {return "CROUCHING";}
}; 

class JumpState:public IMoveState{
public: 
	IMoveState *update(MoveContext *Data) override;
	bool isJumping() const override {return true;}
	std::string getMoveState() const override {return "JUMPING";}
}; 

class ClimbState:public IMoveState{
public: 
	IMoveState *update(MoveContext *Data) override;
	bool isClimbing() const override {return true;}
	std::string getMoveState() const override {return "CLIMBING";}
}; 

class ShootState:public IMoveState{
public: 
	IMoveState *update(MoveContext *Data) override;
	std::string getMoveState() const override {return "SHOOTING";}
}; 