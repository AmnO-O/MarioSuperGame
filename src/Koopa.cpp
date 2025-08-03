#include "Character/Koopa.h"
#include "Character/Character.h"
#include "Blocks/Block.h"

void Koopa::update(float deltaTime) {
    if (dead) {
        velocity = { 0, 0 };
        return;
    }

    if (state == KoopaState::SHELL && !isSpinning) {
        shellTimer += deltaTime;
        if (shellTimer >= shellDuration) {
            exitShell();
        }
    }

    Enemy::update(deltaTime);
}

void Koopa::updateAnimationType() {
    switch (state) {
        case KoopaState::RUNNING:
            if (velocity.x < 0) 
                activeAnimation = animations["WALKLEFT"].get();
            else activeAnimation = animations["WALKRIGHT"].get();
            break;
        case KoopaState::SHELL:
            activeAnimation = animations["SHELL"].get();
            break;
        case KoopaState::SPINNING:
            activeAnimation = animations["SPINNING"].get();
            break;
    }
    updateHitbox();
}

void Koopa::adaptCollision(ICollidable* other) {
    Player* player = dynamic_cast<Player*>(other);
    if (player) {
        Rectangle playerHitbox = player->getHitbox();

        if (playerHitbox.y + playerHitbox.height <= hitbox.y + 5) {
            if (state == KoopaState::RUNNING) {
                position.y += 10.0f;
                enterShell();
            } 
            else if (state == KoopaState::SHELL) {
                startSpinning();
            }
            else if (state == KoopaState::SPINNING) {
                stopSpinning();
                enterShell();
            }
        } 
        else {
            if (state == KoopaState::SHELL && canBePushed) {
                float pushDirection = (playerHitbox.x < hitbox.x) ? -1.0f : 1.0f;
                pushShell(pushDirection);
            }
        }
    }
    
    Enemy* enemy = dynamic_cast<Enemy*>(other);
    if (enemy && enemy != this) {
        if (state == KoopaState::SPINNING) {
            enemy->setDead();
        }
        else if (state == KoopaState::RUNNING) {
            velocity.x = -velocity.x;
        }
        else if (state == KoopaState::SHELL && velocity.x != 0) {
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
    state = KoopaState::SHELL;
    velocity.x = 0;
    shellTimer = 0.0f;
    canBePushed = true;
    updateAnimationType();
}

void Koopa::exitShell() {
    state = KoopaState::RUNNING;
    velocity.x = (velocity.x >= 0 ? 1 : -1) * normalSpeed;
    position.y -= 10.0f;
    shellTimer = 0.0f;
    canBePushed = false;
    updateAnimationType();
}

void Koopa::startSpinning() {
    state = KoopaState::SPINNING;
    velocity.x = (velocity.x >= 0 ? 1 : -1) * spinSpeed;
    isSpinning = true;
    canBePushed = false;
    updateAnimationType();
}

void Koopa::stopSpinning() {
    state = KoopaState::SHELL;
    velocity.x = 0;
    isSpinning = false;
    shellTimer = 0.0f;
    canBePushed = true;
    updateAnimationType();
}

void Koopa::pushShell(float direction) {
    if (state == KoopaState::SHELL && canBePushed) {
        velocity.x = pushSpeed * direction;
        isSpinning = true;
        canBePushed = false;
    }
}