#include "Character/Goomba.h"
#include "Blocks/Coin.h"
#include "Character/Character.h"
#include "Resources/SoundManager.h"
#include "Resources/StatsManager.h"

void Goomba::update(float deltaTime) {
    if (state == State::DIE) {
        velocity = { 0, 0 };
        delayDead += deltaTime;
        if (delayDead >= 0.5f) setDead();
    }

    if (state == State::DIE2) {
        velocity.y = 10.0f;
        delayDead += deltaTime;
        if (delayDead >= 0.0f) setDead2();
    }

    Enemy::update(deltaTime);
}

void Goomba::updateAnimationType() {
    if (state == State::DIE) {
        position.y += hitbox.height * 0.5f;
        hitbox.y = 0.0f;
        activeAnimation = animations["DIE"].get();
        StatsManager::getInstance().addScore(100);
    } 
    else activeAnimation = animations["RUNNING"].get();
    updateHitbox();
}

void Goomba::setDead2() {
    falling = true;
    velocity = {0.0f, 150.0f};
}

void Goomba::adaptCollision(ICollidable* other) {
    if (dynamic_cast<Coin*>(other) || (dynamic_cast<GameObject*>(other) && !dynamic_cast<Fireball*>(other))) return;

    Enemy::adaptCollision(other);
    Player* player = dynamic_cast<Player*>(other);
    if (player) {
        Rectangle playerHitbox = player->getHitbox();

        if (playerHitbox.y + playerHitbox.height <= hitbox.y + 5) {
            if (state == State::RUNNING) {
                state = State::DIE;
                PlaySound(SoundManager::getInstance().stompSound);
                updateAnimationType();
            }
        }
    }
}
