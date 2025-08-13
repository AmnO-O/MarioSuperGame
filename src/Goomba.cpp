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

    Enemy::update(deltaTime);
}

void Goomba::updateAnimationType() {
    switch (state) {
        case State::RUNNING:
            activeAnimation = animations["RUNNING"].get();
            break;
        case State::DIE:
            position.y += hitbox.height * 0.5f;
            activeAnimation = animations["DIE"].get();
            StatsManager::getInstance().addScore(100);
            break;
        case State::DIE2:
            activeAnimation = animations["DIE2"].get();
            break;
    }
    updateHitbox();
}

void Goomba::adaptCollision(ICollidable* other) {
    if (dynamic_cast<Coin*>(other) || (dynamic_cast<GameObject*>(other) && !dynamic_cast<Fireball*>(other))) return;

    Enemy::adaptCollision(other);
    Player* player = dynamic_cast<Player*>(other);
    if (player) {
        Rectangle playerHitbox = player->getHitbox();

        if (player->isInvincible()) {
            if (state != State::DIE && state != State::DIE2) {
                state = State::DIE2;
                PlaySound(SoundManager::getInstance().stompSound);
                updateAnimationType();
            }
        }
        
        if (playerHitbox.y + playerHitbox.height <= hitbox.y + 5) {
            if (state == State::RUNNING) {
                state = State::DIE;
                PlaySound(SoundManager::getInstance().stompSound);
                updateAnimationType();
            }
        }
    }
}
