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


class IMoveState{
public: 
	IMoveState() = default; 
	virtual void update(float deltaTime) = 0; 
	virtual std::string getMoveState() const = 0;
	virtual ~IMoveState() = default;  
};

class StandState: public IMoveState{
public:
	void update(float deltaTime) override; 
	std::string getMoveState() const override {return "STAND";}
};