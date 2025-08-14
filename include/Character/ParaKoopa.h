#pragma once
#include "Enemy.h"

class ParaKoopa : public Enemy {
private:
    float timer = 0.0f;
public:
    ParaKoopa(Vector2 pos) : Enemy(CharacterType::PARA_KOOPA, pos) {
        state = FLYING;
        velocity.y = 20.0f;
        readRectAnimation("assets/animation/parakoopa.txt", Images::textures["enemies1.png"]);
    }

    bool IsActive() const override {
        return state != State::DIE && state != State::DIE2;
    }
    void update(float deltaTime) override;
    void updateAnimationType() override;
    void adaptCollision(ICollidable* other) override;
};