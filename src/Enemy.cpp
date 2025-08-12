#include "Character/Enemy.h"
#include "Blocks/Block.h"

Enemy::Enemy(CharacterType type, Vector2 pos) : type(type) {
    this->position = pos;
    this->groundLevel = 10000.0f;
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

        animations[key] = std::make_unique<AnimationManager>(sheet, 0, 0.2f);
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
    if (state == State::DIE2) {
        velocity = {0.0f, -75.0f};
        delayDead += deltaTime;
        if (delayDead >= 0.2f) setDead2();
    }

    if (state != State::DIE2) 
        velocity.y += 300 * deltaTime;
        
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
    Enemy* enemy = dynamic_cast<Enemy*>(other);
    if (enemy && enemy != this) {
        if (state == State::RUNNING) {
            if (enemy->state == State::RUNNING)
                velocity.x = -velocity.x;
            else if ((enemy->state == State::SHELL && velocity.x != 0) || enemy->state == State::SPINNING) {
                state = State::DIE2;
                updateAnimationType();
            }
        }
    }

    if (falling) return ;

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
                updateAnimationType();
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