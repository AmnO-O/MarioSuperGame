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
    float shellTimer = 0.0f;
    float shellDuration = 3.0f;
    bool isSpinning = false;
    float spinSpeed = 150.0f;
    float normalSpeed = 35.0f;
    bool canBePushed = false;
    float pushSpeed = 80.0f;
    
public:
    Koopa(Vector2 pos) : Enemy(CharacterType::KOOPA, pos) {
        velocity.x = -normalSpeed;
        readRectAnimation("assets/animation/koopa.txt", Images::textures["enemies1.png"]);
    }

    void update(float deltaTime) override;
    void updateAnimationType() override;
    void adaptCollision(ICollidable* other) override;
    
    // Các phương thức mới
    void enterShell();
    void exitShell();
    void startSpinning();
    void stopSpinning();
    void pushShell(float direction); // Đẩy shell theo hướng
    bool isInShell() const { return state == KoopaState::SHELL; }
    bool isSpinningState() const { return state == KoopaState::SPINNING; }
    bool canBePushedState() const { return canBePushed && state == KoopaState::SHELL; }
};