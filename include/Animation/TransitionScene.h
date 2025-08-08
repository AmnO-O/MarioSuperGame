#pragma once
#include "Character/Character.h"


class LevelTransition{
public: 
    virtual void activate() = 0; 

}; 

class CastleTransition : public LevelTransition{
public: 
    void activate() override{

    }
}; 

class PipeTransition : public LevelTransition{
public:
    void activate() override{

    }
}; 

