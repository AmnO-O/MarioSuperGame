#pragma once
#include "Character.h"
#include "Observer/ICollidable.h"

class Enemy : public Character, public ICollidable {
protected:
    CharacterType type;
    std::map<std::string, std::unique_ptr<AnimationManager>> animations;

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

    void adaptCollision(ICollidable* other) override;

    ~Enemy() {}
};
