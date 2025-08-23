#include "Enemy/Blaze.h"
#include "Blocks/Coin.h"
#include "Character/Character.h"
#include "Resources/SoundManager.h"
#include "Resources/StatsManager.h"

void Blaze::update(float deltaTime) {
    if (target.y != 0.0f) {
        if (abs(position.y - target.y) > 2.0f) 
            velocity.y = position.y < target.y ? targetSpeed : -targetSpeed;
        else 
            velocity.y = 0.0f;
    }

    Enemy::update(deltaTime);
}

void Blaze::updateAnimationType() {
    switch (state) {
        case State::FLYING:
            if (!dir)
                activeAnimation = animations["FLYINGLEFT"].get();
            else
                activeAnimation = animations["FLYINGRIGHT"].get();
            break;
    }
    updateHitbox();
}