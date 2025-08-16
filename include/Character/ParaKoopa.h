#pragma once
#include "Koopa.h"

class ParaKoopa : public Koopa {
private:
    float timer = 0.0f;
public:
    ParaKoopa(Vector2 pos) : Koopa(pos, 2) {
        state = FLYING;
        velocity = {0.0f, 20.0f};
        readRectAnimation("assets/animation/parakoopa.txt", Images::textures["enemies1.png"]);
    }
    
    void update(float deltaTime) override;
    void updateAnimationType() override;
    void adaptCollision(ICollidable* other) override;
};