#pragma once
#include "raylib.h"

enum class ShapeState{
    SMALL, BIG, FIRE, TRANSFORMED
}; 

enum class MoveState{
    STAND, SKID, RUN, JUMP, CROUCH
}; 

enum class CharacterType{
    MARIO, LUIGI
}; 

