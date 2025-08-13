#pragma once
#include "Enemy.h"

class Koopa : public Enemy, public IFallable {
private:
    float shellTimer = 0.0f;
    float shellDuration = 3.0f;
    bool isSpinning = false;
    float spinSpeed = 150.0f;
    float normalSpeed = 20.0f;
    bool canBePushed = false;
    float pushSpeed = 80.0f;
    
public:
    Koopa(Vector2 pos) : Enemy(CharacterType::KOOPA, pos) {
        velocity = {-normalSpeed, 50.0f};
        readRectAnimation("assets/animation/koopa.txt", Images::textures["enemies1.png"]);
    }

    bool IsActive() const override {
        return state != State::DIE && state != State::DIE2;
    }
    Rectangle getHitbox() const override { return hitbox; }
    void setGroundLevel(float groundlevel_) override { Character::setGroundLevel(groundlevel_); }

    void update(float deltaTime) override;
    void updateAnimationType() override;
    void adaptCollision(ICollidable* other) override;
    
    void enterShell();
    void exitShell();
    void startSpinning();
    void stopSpinning();
    void pushShell(float direction);
    bool isInShell() const { return state == State::SHELL; }
    bool isSpinningState() const { return state == State::SPINNING; }
    bool canBePushedState() const { return canBePushed && state == State::SHELL; }
};