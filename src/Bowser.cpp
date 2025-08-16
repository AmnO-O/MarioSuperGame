#include "Character/Bowser.h"
#include "Blocks/Coin.h"
#include "Character/Character.h"
#include "Resources/SoundManager.h"
#include "Resources/StatsManager.h"

void Bowser::update(float deltaTime) {
    if (state == State::DIE2) {
        velocity = {20.0f, -75.0f};
        delayDead += deltaTime;
        if (delayDead >= 0.2f) setDead2();
    }

    if (hitbox.y + hitbox.height < opos && state != DIE2) {
        if (position.y + activeAnimation->getCurrentShape().y < groundLevel)
            velocity.y += 300 * deltaTime;
        else velocity.y = 0;
    }
    
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;

    if (activeAnimation) {
        activeAnimation->update(deltaTime);
        updateHitbox();
    }

    if (jumpTimer < jumpInterval) {
        jumpTimer += deltaTime;
    } 
    else {
        jumpTimer = 0.0f;
        jumpCount ++;
        if (jumpCount == maxJumpCount) {
            velocity.x = -velocity.x;
            jumpCount = 0;
        }
        velocity.y = jumpSpeed;
    }

    if (atkTimer < atkSpeed) {
        atkTimer += deltaTime;
    }
    else {
        atkTimer = 0.0f;
        atk.push_back({position.x - 12.0f, position.y + 12.0f});
    }
}

void Bowser::updateAnimationType() {
    switch (state) {
        case State::RUNNING:
            activeAnimation = animations["WALKLEFT"].get();
            break;
        case State::ATTACKING:
            activeAnimation = animations["ATKLEFT"].get();
            break;
        case State::DIE2:
            position.y += 15.0f;
            activeAnimation = animations["DIE2"].get();
            break;
    }
    updateHitbox();
}

void Bowser::adaptCollision(ICollidable* other) {
    if (dynamic_cast<Coin*>(other) || (dynamic_cast<GameObject*>(other) && !dynamic_cast<Fireball*>(other))) return;

    Enemy::blockCollision(other);

    Player* player = dynamic_cast<Player*>(other);
    if (player) {
        Rectangle playerHitbox = player->getHitbox();

        if (player->isInvincible()) {
            if (state != State::DIE2) {
                state = State::DIE2;
                PlaySound(SoundManager::getInstance().stompSound);
                updateAnimationType();
                StatsManager::getInstance().addScore(5000);
            }
        }
    }

    Fireball* fireball = dynamic_cast<Fireball*>(other);
    if (fireball) {
        hp -= state != State::DIE2 && fireball->isActive();
    }

    if (hp <= 0 && state != State::DIE2) {
        state = State::DIE2;
        PlaySound(SoundManager::getInstance().stompSound);
        updateAnimationType();
        StatsManager::getInstance().addScore(5000);
    }
}
