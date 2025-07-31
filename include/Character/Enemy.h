#pragma once
#include "Character/Character.h"
#include "Observer/ICollidable.h"

class Enemy : public Character, public ICollidable {
protected:
    bool alive = true;

public:
    Enemy(Vector2 pos);
    virtual ~Enemy() = default;

    Rectangle getHitbox() const override;
    bool IsActive() const override;
    void kill();
    virtual void adaptCollision(ICollidable* other) override;
};
