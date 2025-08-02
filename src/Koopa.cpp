#include "Character/Koopa.h"
#include "Character/Character.h"

void Koopa::update(float deltaTime) {
    if (dead) {
        velocity = { 0, 0 };
    }

    Enemy::update(deltaTime);
}

void Koopa::updateAnimationType() {
    if (state == KoopaState::SHELL) {
        position.y += 10.0f;
        activeAnimation = animations["SHELL"].get();
    } 
    else activeAnimation = animations["RUNNING"].get();
    updateHitbox();
}

void Koopa::adaptCollision(ICollidable* other) {
    Player* player = dynamic_cast<Player*>(other);
    if (player) {
        Rectangle playerHitbox = player->getHitbox();

        if (playerHitbox.y + playerHitbox.height <= hitbox.y + 5) {
            if (state == KoopaState::RUNNING) {
                state = KoopaState::SHELL;
                velocity.x = 0;
                updateAnimationType();
            } 
            // else if (state == KoopaState::SHELL) {
            //     state = KoopaState::SPINNING;
            //     updateAnimationType();
            // } 
            // Handle other states if necessary
        } 
        else {
            // Nếu va chạm ngang => player mất mạng (handle ở Player)
            // Có thể set 1 flag để Player xử lý khi va chạm với enemy
        }
    }
}