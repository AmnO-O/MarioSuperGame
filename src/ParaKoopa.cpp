#include "Character/ParaKoopa.h"
#include "Character/Character.h"
#include "Blocks/Block.h"
#include "Blocks/Coin.h"
#include "Resources/SoundManager.h"
#include "Resources/StatsManager.h"

void ParaKoopa::update(float deltaTime) {
    
    timer += deltaTime;
    if (timer >= 2.0f) {
        velocity.y = -velocity.y;
        timer = 0.0f;
    }   

    Enemy::update(deltaTime);
}

void ParaKoopa::updateAnimationType() {
    if (state == State::DIE2) {
        position.y += 10.0f;
        activeAnimation = animations["DIE2"].get();
    } 
    else activeAnimation = animations["RUNNING"].get();
    updateHitbox();
}

void ParaKoopa::adaptCollision(ICollidable* other) {
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
                state = State::DIE2;
                updateAnimationType();
            }
        }
    }
}
