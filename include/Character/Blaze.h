#pragma once
#include "Enemy.h"

class Blaze : public Enemy {
public:
    Blaze(Vector2 pos) : Enemy(CharacterType::BLAZE, pos) {
        state = State::FLYING;
        velocity = {-60.0f, 0.0f};
        readRectAnimation("assets/animation/blaze.txt", Images::textures["enemies_sprites.png"]);
    }

    void update(float deltaTime) override;
    void updateAnimationType() override;
    void adaptCollision(ICollidable* other) override {};
};