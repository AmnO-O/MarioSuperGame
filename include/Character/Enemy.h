#pragma once
#include "Character.h"
#include "Blocks/Block.h"
#include "Observer/ICollidable.h"

enum State {
    RUNNING,
    SHELL,
    SPINNING,
    FLYING,
    ATTACKING,
    DIE,
    DIE2
};

class Enemy : public Character, public ICollidable {
protected:
    DrawStat ds = DrawStat::First;
    CharacterType type;
    bool falling = false;
    float delayDead = 0.0f; 
    std::map<std::string, std::unique_ptr<AnimationManager>> animations;

    void readRectAnimation(const std::string& filePath, Texture2D& sheet) ;

public:
    State state = RUNNING;
    Enemy(CharacterType type, Vector2 pos);

    virtual void updateAnimationType() = 0;
    void update(float deltaTime) override;
    void render() override;
    void Draw(DrawStat stat);

    CharacterType getType() const {return type;}
    Rectangle getHitbox() const override { return hitbox; }
    Vector2 getPosition() const { return position; }

    void setPosition(const Vector2& pos);
    void setOnGround();
    void setGroundLevel(float groundlevel_) override { Character::setGroundLevel(groundlevel_); }

    void setDead();
    virtual void setDead2() {falling = true; velocity = {0.0f, 150.0f};};
    bool isDead() const { return dead; }
    bool IsActive() const override { return !dead; }
    virtual bool isSafe() const { return state == State::SHELL || state == State::DIE || state == State::DIE2; }
    void isHitBelow(ICollidable* block) override;

    void enemyCollision(ICollidable* other);
    void blockCollision(ICollidable* other);
    void fireballCollision(ICollidable* other);
    void adaptCollision(ICollidable* other) override;

    ~Enemy() {}
};