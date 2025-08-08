#include "Character/Goomba.h"
#include "Blocks/Coin.h"
#include "Character/Character.h"

void Goomba::update(float deltaTime) {
    if (state == State::DIE) {
        velocity = { 0, 0 };
        delayDead += deltaTime;
        if (delayDead >= 0.5f) setDead();
    }

    Enemy::update(deltaTime);
}

void Goomba::updateAnimationType() {
    if (state == State::DIE) {
        position.y += hitbox.height * 0.5f;
        activeAnimation = animations["DIE"].get();
    } 
    else activeAnimation = animations["RUNNING"].get();
    updateHitbox();
}

void Goomba::adaptCollision(ICollidable* other) {
    if (dynamic_cast<Coin*>(other) || (dynamic_cast<GameObject*>(other) && !dynamic_cast<Fireball*>(other))) return;
    Player* player = dynamic_cast<Player*>(other);
    if (player) {
        Rectangle playerHitbox = player->getHitbox();

        if (playerHitbox.y + playerHitbox.height <= hitbox.y + 5) {
            if (state == State::RUNNING) {
                state = State::DIE;
                updateAnimationType();
            }
        }
    }

    Enemy* enemy = dynamic_cast<Enemy*>(other);
    if (enemy && enemy != this) {
        if (state == State::RUNNING) {
            velocity.x = -velocity.x;
        }
    }
}
