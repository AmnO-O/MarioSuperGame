#pragma once
#include "Enemy.h"

class Goomba : public Enemy {
public:
    Goomba(Vector2 pos) : Enemy(CharacterType::GOOMBA, pos) {
        velocity.x = -35.0f;
        readRectAnimation("assets/animation/goomba.txt", Images::textures["enemies1.png"]);
    }

    void update(float deltaTime) override;
    void updateAnimationType() override;
    void setDead2() override;
    void adaptCollision(ICollidable* other) override;
};
