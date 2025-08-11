#include "Character/Piranha.h"
#include "Character/Character.h"

void Piranha::update(float deltaTime) {
    if (isGoing) {
        timer += deltaTime;
        if (timer >= 0.5f) {
            velocity.y = -velocity.y;
            timer = 0.0f;
        }   
    }

    Enemy::update(deltaTime);
}

void Piranha::updateAnimationType() {
    activeAnimation = animations["RUNNING"].get();
    updateHitbox();
}