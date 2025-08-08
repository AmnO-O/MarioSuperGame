#include "Character/Koopa.h"
#include "Character/Character.h"
#include "Blocks/Block.h"
#include "Blocks/Coin.h"

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
    }
    updateHitbox();
}

void Koopa::adaptCollision(ICollidable* other) {
    if (dynamic_cast<Coin*>(other) || (dynamic_cast<GameObject*>(other) && !dynamic_cast<Fireball*>(other))) return;
    Player* player = dynamic_cast<Player*>(other);
    if (player) {
        Rectangle playerHitbox = player->getHitbox();

        if (playerHitbox.y + playerHitbox.height <= hitbox.y + 5) {
            if (state == State::RUNNING) {
                position.y += 10.0f;
                enterShell();
            } 
            else if (state == State::SHELL) {
                velocity.x = (playerHitbox.x < hitbox.x) ? 1.0f : -1.0f;
                startSpinning();
            }
            else if (state == State::SPINNING) {
                stopSpinning();
                enterShell();
            }
        } 
        else {
            if (state == State::SHELL && canBePushed) {
                float pushDirection = (playerHitbox.x < hitbox.x) ? -1.0f : 1.0f;
                pushShell(pushDirection);
            }
        }
    }
    
    Enemy* enemy = dynamic_cast<Enemy*>(other);
    if (enemy && enemy != this) {
        if (state == State::SPINNING) {
            enemy->setDead();
        }
        else if (state == State::RUNNING) {
            velocity.x = -velocity.x;
        }
        else if (state == State::SHELL && velocity.x != 0) {
            enemy->setDead();
        }
    }
    
    Block* block = dynamic_cast<Block*>(other);
    if (block) {
        Rectangle blockHitbox = block->getHitbox();
        
        if (velocity.x != 0) {
            if (velocity.x > 0 && hitbox.x + hitbox.width > blockHitbox.x && 
                hitbox.x < blockHitbox.x) {
                velocity.x = -velocity.x;
                updateAnimationType();
                position.x = blockHitbox.x - hitbox.width;
            }
            else if (velocity.x < 0 && hitbox.x < blockHitbox.x + blockHitbox.width && 
                     hitbox.x + hitbox.width > blockHitbox.x + blockHitbox.width) {
                velocity.x = -velocity.x;
                position.x = blockHitbox.x + blockHitbox.width;
            }
        }
        
        if (velocity.y > 0 && hitbox.y + hitbox.height > blockHitbox.y && 
            hitbox.y < blockHitbox.y) {
            position.y = blockHitbox.y - hitbox.height;
            velocity.y = 0;
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

void Koopa::pushShell(float direction) {
    if (state == State::SHELL && canBePushed) {
        velocity.x = pushSpeed * direction;
        isSpinning = true;
        canBePushed = false;
    }
}