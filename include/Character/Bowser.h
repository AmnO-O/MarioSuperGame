#pragma once
#include "Enemy.h"
#include "Blaze.h"

class Bowser : public Enemy, public IFallable {
private:
    int hp = 100;
    float opos;
    float jumpTimer = 0.0f;
    const float jumpInterval = 3.0f;
    int jumpCount = 0;
    const int maxJumpCount = 3;
    float jumpSpeed = -50.0f;
    float atkTimer = 0.0f;
    float atkSpeed = 2.0f;
    std::vector <Vector2> atk;

public:
    Bowser(Vector2 pos) : Enemy(CharacterType::BOWSER, pos) {
        velocity = {-15.0f, 0.0f};
        opos = pos.y;
        readRectAnimation("assets/animation/bowser.txt", Images::textures["enemies_sprites.png"]);
    }

    bool IsActive() const override {return state != State::DIE2;}
    Rectangle getHitbox() const override { return hitbox; }
    void setGroundLevel(float groundlevel_) override { Character::setGroundLevel(groundlevel_); }

    bool isEmpty() {return atk.size() == 0;}
    Vector2 getMinion() {
        Vector2 tmp = atk.back();
        atk.pop_back();
        return tmp;
    }

    void update(float deltaTime) override;
    void updateAnimationType() override;
    void adaptCollision(ICollidable* other) override;
};