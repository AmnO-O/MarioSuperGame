#pragma once
#include "Enemy.h"

class Blaze : public Enemy {
private:
    bool dir = false;
    Vector2 target;
    const float targetSpeed = 70;
public:
    Blaze(Vector2 pos, Vector2 targ) : Enemy(CharacterType::BLAZE, pos) {
        state = State::FLYING, target = targ;
        velocity = {-60.0f, 0.0f};
        if (pos.x < targ.x) dir = 1, velocity.x *= -1;
        readRectAnimation("assets/animation/blaze.txt", Images::textures["enemies_sprites.png"]);
    }

    void update(float deltaTime) override;
    void updateAnimationType() override;
    void adaptCollision(ICollidable* other) override {};
};