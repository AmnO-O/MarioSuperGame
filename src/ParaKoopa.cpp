#include "Character/ParaKoopa.h"
#include "Character/Character.h"
#include "Blocks/Block.h"
#include "Blocks/Coin.h"
#include "Resources/SoundManager.h"
#include "Resources/StatsManager.h"

void ParaKoopa::update(float deltaTime) {
    Koopa::update(deltaTime);

    if (state == State::FLYING) {
        timer += deltaTime;
        if (timer >= 3.5f) {
            velocity.y = -velocity.y;
            timer = 0.0f;
        }
    }
}

void ParaKoopa::updateAnimationType() {
    if (state == State::FLYING) 
        activeAnimation = animations["FLYING"].get();
    Koopa::updateAnimationType();
}

void ParaKoopa::adaptCollision(ICollidable* other) {
    if (dynamic_cast<Coin*>(other) || (dynamic_cast<GameObject*>(other) && !dynamic_cast<Fireball*>(other))) return;

    if (state == State::FLYING) {
        enemyCollision(other);
        fireballCollision(other);

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
                if (state == State::FLYING) {
                    state = State::RUNNING;
                    position.y += 10.0f;
                    velocity.x = -normalSpeed;
                    updateAnimationType();
                }
            }
        }   
    }
    else {
        Koopa::adaptCollision(other);
    }
}
