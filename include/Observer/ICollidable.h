#ifndef ICOLLIDABLE_H
#define ICOLLIDABLE_H

#include "raylib.h"
#include <vector>


class ICollidable {
public:
    virtual Rectangle getHitbox() const = 0;
    virtual void adaptCollision(ICollidable* other) = 0;
    virtual bool IsActive() const { return true; } 
    virtual void isHitBelow(ICollidable* block) { return; }
    virtual ~ICollidable() = default;
};

class IFallable {
public:
    virtual Rectangle getHitbox() const = 0;
    virtual bool IsActive() const = 0;
    virtual void setGroundLevel(float groundlevel) = 0;
    virtual ~IFallable() = default;
};

#endif
