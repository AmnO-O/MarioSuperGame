#pragma once
#include "Character.h"
#include "Observer/ICollidable.h"

enum State {
    RUNNING,
    SHELL,
    SPINNING,
    DIE,
    DIE2
};

class Enemy : public Character, public ICollidable {
protected:
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

    Rectangle getHitbox() const override { return hitbox; }
    Vector2 getPosition() const { return position; }

    void setPosition(const Vector2& pos);
    void setOnGround();

    void setDead();
    virtual void setDead2() {};
    bool isDead() const { return dead; }
    bool IsActive() const override { return !dead; }
    bool isSafe() const { return state == State::SHELL || state == State::DIE2; }

    void adaptCollision(ICollidable* other) override;

    ~Enemy() {}
};
