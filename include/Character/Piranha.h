#pragma once
#include "Enemy.h"

class Piranha : public Enemy {
private:
    bool isGoing;
    float timer = 0.0f;
public:
    Piranha(Vector2 pos, bool ig) : Enemy(CharacterType::PIRANHA, pos) {
        isGoing = ig;
        velocity.y = (isGoing ? 10.0f : 0.0f);
        readRectAnimation("assets/animation/piranha.txt", Images::textures["enemies1.png"]);
    }

    void update(float deltaTime) override;
    void updateAnimationType() override;
    void adaptCollision(ICollidable* other) {}
};
