#pragma once
#include "Enemy.h"

enum KoopaState {
    RUNNING,
    SHELL,
    SPINNING
};

class Koopa : public Enemy {
private:
    KoopaState state = RUNNING;
public:
    Koopa(Vector2 pos) : Enemy(CharacterType::KOOPA, pos) {
        velocity.x = -35.0f;
        readRectAnimation("assets/animation/koopa.txt", Images::textures["enemies1.png"]);
    }

    void update(float deltaTime) override;
    void updateAnimationType() override;
    void adaptCollision(ICollidable* other) override;
};