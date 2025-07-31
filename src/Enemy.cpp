#include "Character/Enemy.h"
// #include "Character/Character.h"

Enemy::Enemy(Vector2 pos) {
    this->position = pos;
    this->velocity = { -50.0f, 0 };
}

Rectangle Enemy::getHitbox() const {
    return hitbox;
}

bool Enemy::IsActive() const {
    return !dead;
}

void Enemy::kill() {
    dead = true;
}

void Enemy::adaptCollision(ICollidable* other) {
}
