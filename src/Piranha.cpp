#include "Character/Piranha.h"
#include "Character/Character.h"

void Piranha::update(float deltaTime) {
    Enemy::update(deltaTime);
    if (isGoing) {
        timer += deltaTime;
        if (timer >= 2.0f) {
            velocity.y = -velocity.y;
            timer = 0.0f;
        }   
    }
}

void Piranha::updateAnimationType() {
    activeAnimation = animations["RUNNING"].get();
    updateHitbox();
}