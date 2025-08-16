#include "Character/Blaze.h"
#include "Blocks/Coin.h"
#include "Character/Character.h"
#include "Resources/SoundManager.h"
#include "Resources/StatsManager.h"

void Blaze::update(float deltaTime) {
    if (state == State::DIE) {
        velocity = { 0, 0 };
        delayDead += deltaTime;
        if (delayDead >= 0.5f) setDead();
    }

    Enemy::update(deltaTime);
}

void Blaze::updateAnimationType() {
    switch (state) {
        case State::FLYING:
            activeAnimation = animations["FLYINGLEFT"].get();
            break;
    }
    updateHitbox();
}