#pragma once
#include "Enemy.h"

class Goomba : public Enemy, public IFallable {
public:
    Goomba(Vector2 pos) : Enemy(CharacterType::GOOMBA, pos) {
        velocity = {-20.0f, 50.0f};
        readRectAnimation("assets/animation/goomba.txt", Images::textures["enemies1.png"]);
    }

    bool IsActive() const override {
        return state != State::DIE && state != State::DIE2;
    }
    Rectangle getHitbox() const override { return hitbox; }
    void setGroundLevel(float groundlevel_) override { Character::setGroundLevel(groundlevel_); }

    void update(float deltaTime) override;
    void updateAnimationType() override;
    void adaptCollision(ICollidable* other) override;
};
