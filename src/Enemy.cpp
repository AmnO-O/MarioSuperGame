#include "Character/Enemy.h"

Enemy::Enemy(CharacterType type, Vector2 pos) : type(type) {
    this->position = pos;
    this->groundLevel = 0.0f;
    this->hitbox = { pos.x, pos.y, 16.0f, 16.0f };
    this->activeAnimation = nullptr;
}

void Enemy::readRectAnimation(const std::string& filePath, Texture2D& sheet) {
    std::ifstream fin(filePath);
    if (!fin)
        throw GameException("Failed to open animation file: " + filePath);

    std::string key;
    while (fin >> key) {
        int frameCount;
        fin >> frameCount;

        animations[key] = std::make_unique<AnimationManager>(sheet, 0);
        for (int i = 0; i < frameCount; ++i) {
            int x, y, w, h;
            fin >> x >> y >> w >> h;
            animations[key]->addRect({x * 1.0f, y * 1.0f, w * 1.0f, h * 1.0f});
        }
    }

    updateAnimationType();
    fin.close();
}

void Enemy::update(float deltaTime) {
    if (dead) return;

    // velocity.y += 300 * deltaTime;
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;

    if (activeAnimation) {
        activeAnimation->update(deltaTime);
        updateHitbox();
    }
}

void Enemy::render() {
    if (dead) return;
    
    if (activeAnimation)
        activeAnimation->render(position, false);
}

void Enemy::setPosition(const Vector2& pos) {
    position = pos;
    updateHitbox();
}

void Enemy::setOnGround() {
    position.y = groundLevel - hitbox.height;
    velocity.y = 0;
    updateHitbox();
}

void Enemy::setDead() {
    if (dead) return;
    dead = 1;
}

void Enemy::adaptCollision(ICollidable* other) {
}
