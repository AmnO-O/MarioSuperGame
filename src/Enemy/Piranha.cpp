#include "Enemy/Piranha.h"
#include "Character/Character.h"
#include "Blocks/Block.h"
#include "Blocks/Coin.h"
#include "Resources/SoundManager.h"
#include "Resources/StatsManager.h"

void Piranha::update(float deltaTime) {
    if (state == State::DIE2) {
        velocity = {0, 0};
        setDead();
    }

    if (stop) return ;

    if (isGoing) {
        timer += deltaTime;
        if (timer >= 3.4f) velocity.y = -velocity.y, timer -= 3.4f;   
    }
    
    Enemy::update(deltaTime);

    hidden = (position.y > top - 2.0f);
}

void Piranha::update2(Vector2 ppos) {
    if (state == State::DIE2) return ;
    if (position.x - 5.0f < ppos.x && ppos.x < position.x + hitbox.width + 5.0f) {
        if (ppos.y + 32.0f > top) {
            setHidden();
            stop = true;
        }
    }
    else stop = false;
}

void Piranha::updateAnimationType() {
    activeAnimation = animations["FLYING"].get();
    updateHitbox();
}

void Piranha::setHidden() {
    if (hidden) return ;
    while (!hidden) update(0.2f);
    update(0.2f);
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
            setHidden();
        }
    }
}