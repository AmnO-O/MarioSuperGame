#pragma once
#include "Character/Character.h"


/// @brief 
class LevelTransition{
public: 
    virtual void activate() = 0; 
    virtual void update(float deltaTime) = 0; 
    virtual void render() = 0; 
}; 

class CastleTransition : public LevelTransition{
public: 
    
}; 

class PipeTransition : public LevelTransition{
public:

}; 

