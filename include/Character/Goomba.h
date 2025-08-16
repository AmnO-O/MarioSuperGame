#pragma once
#include "Enemy.h"

class Goomba : public Enemy, public IFallable {
private:
    bool isBrown = true;
public:
    Goomba(Vector2 pos, bool isBrown) : Enemy(CharacterType::GOOMBA, pos) {
        velocity = {-20.0f, 50.0f};
        if (isBrown)
            readRectAnimation("assets/animation/goomba.txt", Images::textures["enemies1.png"]);
        else
            readRectAnimation("assets/animation/goomba_blue.txt", Images::textures["enemies_sprites.png"]);
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