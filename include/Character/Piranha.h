#pragma once
#include "Enemy.h"

class Piranha : public Enemy {
private:
    bool isGoing;
    float timer = 0.0f;
    float top;
    bool hidden;
    bool stop = false;
public:
    Piranha(Vector2 pos, bool ig) : Enemy(CharacterType::PIRANHA, pos) {
        ds = DrawStat::Zero;
        state = FLYING;
        isGoing = ig;
        velocity.y = (isGoing ? 10.0f : 0.0f);
        top = position.y + 25.0f;
        readRectAnimation("assets/animation/piranha.txt", Images::textures["enemies1.png"]);
    }

    bool isSafe() const override {
        return state == State::DIE || hidden;
    }

    void setHidden();
    void update(float deltaTime) override;
    void update2(Vector2 ppos) override;
    void updateAnimationType() override;
    void adaptCollision(ICollidable* other);
};
