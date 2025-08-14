#include "Character/Piranha.h"
#include "Character/Character.h"
#include "Resources/Map.h"
#include "Blocks/Block.h"
#include "Blocks/Coin.h"
#include "Resources/SoundManager.h"
#include "Resources/StatsManager.h"

void Piranha::update(float deltaTime) {
    if (state == State::DIE2) {
        velocity = {0, 0};
        setDead();
    }

    if (isGoing) {
        timer += deltaTime;
        if (timer >= 3.5f) velocity.y = -velocity.y, timer = 0.0f;   
    }
    
    Enemy::update(deltaTime);

    hidden = (position.y > top - 2.0f);
}

void Piranha::updateAnimationType() {
    activeAnimation = animations["FLYING"].get();
    updateHitbox();
}

void Piranha::adaptCollision(ICollidable* other) {
    if (dynamic_cast<Coin*>(other) || (dynamic_cast<GameObject*>(other) && !dynamic_cast<Fireball*>(other))) return;

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

        if (playerHitbox.y + playerHitbox.height <= hitbox.y + 5 && hidden) {
            update(-1.5f);
        }
    }
}