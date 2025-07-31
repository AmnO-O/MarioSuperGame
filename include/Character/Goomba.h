#pragma once
#include "Character/Enemy.h"

class Goomba : public Enemy {
public:
    Goomba(Vector2 pos);

    void update(float deltaTime) override;
    void render() override;
    void adaptCollision(ICollidable* other) override;
};
