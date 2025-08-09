#include "Character/Goomba.h"
#include "Blocks/Coin.h"
#include "Character/Character.h"
#include "Resources/SoundManager.h"
#include "Resources/StatsManager.h"

void Goomba::update(float deltaTime) {
    if (state == GoombaState::DIE) {
        velocity = { 0, 0 };
        delayDead += deltaTime;
        if (delayDead >= 0.5f) setDead();
    }

    Enemy::update(deltaTime);
}

void Goomba::updateAnimationType() {
    if (state == GoombaState::DIE) {
        position.y += hitbox.height * 0.5f;
        activeAnimation = animations["DIE"].get();
        StatsManager::getInstance().addScore(100);
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
            if (state == GoombaState::RUNNING) {
                state = GoombaState::DIE;
                PlaySound(SoundManager::getInstance().stompSound);
                updateAnimationType();
            }
        } 
        else {
            // Nếu va chạm ngang => player mất mạng (handle ở Player)
            // Có thể set 1 flag để Player xử lý khi va chạm với enemy
        }
    }
}
