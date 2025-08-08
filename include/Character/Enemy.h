#pragma once
#include "Character.h"
#include "Observer/ICollidable.h"

enum State {
    RUNNING,
    SHELL,
    SPINNING,
    DIE
};

class Enemy : public Character, public ICollidable {
protected:
    CharacterType type;
    State state = RUNNING;
    std::map<std::string, std::unique_ptr<AnimationManager>> animations;
    float delayDead = 0.0f; 

    void readRectAnimation(const std::string& filePath, Texture2D& sheet) ;

public:
    Enemy(CharacterType type, Vector2 pos);

    virtual void updateAnimationType() = 0;
    void update(float deltaTime) override;
    void render() override;

    Rectangle getHitbox() const override { return hitbox; }
    Vector2 getPosition() const { return position; }

    void setPosition(const Vector2& pos);
    void setOnGround();

    void setDead();
    bool isDead() const { return dead; }
    bool IsActive() const override { return !dead; }

    void adaptCollision(ICollidable* other) override;

    ~Enemy() {}
};
