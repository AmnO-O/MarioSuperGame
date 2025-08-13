#include "Character/Piranha.h"
#include "Character/Character.h"

void Piranha::update(float deltaTime) {    if (dead) return;
    if (state == State::DIE2) {
        velocity = {20.0f, -75.0f};
        delayDead += deltaTime;
        if (delayDead >= 0.2f) setDead2();
    }
    
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;

    if (activeAnimation) {
        activeAnimation->update(deltaTime);
        updateHitbox();
    }

    if (isGoing) {
        timer += deltaTime;
        if (timer >= 3.0f) {
            velocity.y = -velocity.y;
            timer = 0.0f;
        }   
    }
}

void Piranha::updateAnimationType() {
    activeAnimation = animations["RUNNING"].get();
    updateHitbox();
}