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

    if (position.y + activeAnimation->getCurrentShape().y < groundLevel)
        velocity.y += 300 * deltaTime;
    else
        velocity.y = 0;
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
        Rectangle blockBox = other->getHitbox();
        Rectangle enemyBox = getHitbox();

        // Check if overlapping
        if (!CheckCollisionRecs(enemyBox, blockBox)) return;

        // Calculate overlaps
        float overlapLeft   = (enemyBox.x + enemyBox.width) - blockBox.x;
        float overlapRight  = (blockBox.x + blockBox.width) - enemyBox.x;
        float overlapTop    = (enemyBox.y + enemyBox.height) - blockBox.y;
        float overlapBottom = (blockBox.y + blockBox.height) - enemyBox.y;

        // Find smallest overlap
        float minOverlap = overlapLeft;
        enum Dir { LEFT, RIGHT, TOP, BOTTOM } dir = LEFT;

        if (overlapRight < minOverlap) { minOverlap = overlapRight; dir = RIGHT; }
        if (overlapTop < minOverlap)   { minOverlap = overlapTop;   dir = TOP; }
        if (overlapBottom < minOverlap){ minOverlap = overlapBottom;dir = BOTTOM; }

        // Resolve collision
        switch (dir) {
            case LEFT:
                position.x -= overlapLeft;
                velocity.x = -velocity.x;
                break;
            case RIGHT:
                position.x += overlapRight;
                velocity.x = -velocity.x;
                break;
            case TOP:
                position.y -= overlapTop;
                velocity.y = 0;
                setGroundLevel(blockBox.y);
                setOnGround();
                break;
            case BOTTOM:
                position.y += overlapBottom;
                velocity.y = 0; // Or small bounce
                break;
        }

        updateHitbox();
    }
}