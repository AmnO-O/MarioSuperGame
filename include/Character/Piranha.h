#pragma once
#include "Enemy.h"

class Piranha : public Enemy {
private:
    bool isGoing;
    float timer = 0.0f;
    float top;
    bool hidden;
public:
    Piranha(Vector2 pos, bool ig) : Enemy(CharacterType::PIRANHA, pos) {
        state = FLYING;
        isGoing = ig;
        velocity.y = (isGoing ? 10.0f : 0.0f);
        top = position.y + 25.0f;
        readRectAnimation("assets/animation/piranha.txt", Images::textures["enemies1.png"]);
    }

    bool isSafe() const override {
        return state == State::DIE || hidden;
    }

    void update(float deltaTime) override;
    void updateAnimationType() override;
    void adaptCollision(ICollidable* other);
};
