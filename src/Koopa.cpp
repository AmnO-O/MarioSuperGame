#include "Character/Koopa.h"
#include "Character/Character.h"
#include "Blocks/Block.h"
#include "Blocks/Coin.h"
#include "Resources/SoundManager.h"
#include "Resources/StatsManager.h"

void Koopa::update(float deltaTime) {
    if (dead) {
        velocity = { 0, 0 };
        return;
    }

    if (state == State::SHELL && !isSpinning) {
        shellTimer += deltaTime;
        if (shellTimer >= shellDuration) {
            exitShell();
        }
    }

    Enemy::update(deltaTime);
}

void Koopa::updateAnimationType() {
    switch (state) {
        case State::RUNNING:
            if (velocity.x < 0) 
                activeAnimation = animations["WALKLEFT"].get();
            else activeAnimation = animations["WALKRIGHT"].get();
            break;
        case State::SHELL:
            activeAnimation = animations["SHELL"].get();
            break;
        case State::SPINNING:
            activeAnimation = animations["SPINNING"].get();
            break;
        case State::DIE2:
            position.y += 10.0f;
            activeAnimation = animations["DIE2"].get();
            break;
    }
    updateHitbox();
}

void Koopa::adaptCollision(ICollidable* other) {
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
                StatsManager::getInstance().addScore(300);
            }
        }

        if (playerHitbox.y + playerHitbox.height <= hitbox.y + 5) {
            if (state == State::RUNNING) {
                position.y += 10.0f;
                PlaySound(SoundManager::getInstance().stompSound);
                StatsManager::getInstance().addScore(200);
                enterShell();
            } 
            else if (state == State::SHELL) {
                velocity.x = (playerHitbox.x < hitbox.x) ? 1.0f : -1.0f;
                startSpinning();
                PlaySound(SoundManager::getInstance().stompSound);
                StatsManager::getInstance().addScore(500);
            }
            else if (state == State::SPINNING) {
                stopSpinning();
                enterShell();
                StatsManager::getInstance().addScore(700);
            }
        } 
        else if (playerHitbox.x + playerHitbox.width <= hitbox.x + 5 || 
                 playerHitbox.x >= hitbox.x + hitbox.width - 5) {
            if (state == State::SHELL) {
                velocity.x = (playerHitbox.x < hitbox.x) ? 1.0f : -1.0f;
                startSpinning();
                PlaySound(SoundManager::getInstance().stompSound);
                StatsManager::getInstance().addScore(500);
            }
        }
    }
    
    if (type != 2) return ;

    Block* block = dynamic_cast<Block*>(other);
    if (block) {
        Rectangle blockBox = other->getHitbox();
        Rectangle enemyBox = getHitbox();
        
        if (CheckCollisionRecs(enemyBox, blockBox)) return;

        if (enemyBox.y < blockBox.y) {
            if (enemyBox.x < blockBox.x - 6.0f || enemyBox.x + enemyBox.width > blockBox.x + blockBox.width + 6.0f) {
                position.x += (enemyBox.x < blockBox.x) ? 2.0f : -2.0f;
                velocity.x = -velocity.x;
                updateAnimationType();
            }
        }
    }
}

void Koopa::enterShell() {
    state = State::SHELL;
    velocity.x = 0;
    shellTimer = 0.0f;
    canBePushed = true;
    updateAnimationType();
}

void Koopa::exitShell() {
    state = State::RUNNING;
    velocity.x = (velocity.x >= 0 ? 1 : -1) * normalSpeed;
    position.y -= 10.0f;
    shellTimer = 0.0f;
    canBePushed = false;
    updateAnimationType();
}

void Koopa::startSpinning() {
    state = State::SPINNING;
    velocity.x = (velocity.x >= 0 ? 1 : -1) * spinSpeed;
    isSpinning = true;
    canBePushed = false;
    updateAnimationType();
}

void Koopa::stopSpinning() {
    state = State::SHELL;
    velocity.x = 0;
    isSpinning = false;
    shellTimer = 0.0f;
    canBePushed = true;
    updateAnimationType();
}