#pragma once
#include "Enemy.h"

enum class GoombaState {
    RUNNING,
    DIE
};

class Goomba : public Enemy {
private:
    GoombaState state = GoombaState::RUNNING;
public:
    Goomba(Vector2 pos) : Enemy(CharacterType::GOOMBA, pos) {
        velocity.x = -35.0f;
        readRectAnimation("assets/animation/goomba.txt", Images::textures["enemies1.png"]);
    }

    void update(float deltaTime) override;
    void updateAnimationType() override;
    void adaptCollision(ICollidable* other) override;
};
