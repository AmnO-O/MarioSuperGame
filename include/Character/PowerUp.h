#pragma once
#include "Global.h"
#include "GameObject.h"
#include "Animation.h"
#include "Observer/ICollidable.h"
#include <iostream>
class Player;

class PowerUp : public GameObject, public ICollidable {
protected:
    PowerUpType type;
    AnimationManager *activeAnimation;

public:
    PowerUp(PowerUpType t, Vector2 pos)
        : type(t), GameObject(pos, {0.0f, 0.0f}), activeAnimation(nullptr) {
        hitbox = {pos.x, pos.y, 16.0f, 16.0f};
    }

    virtual ~PowerUp() { delete activeAnimation; }

    virtual void applyEffect(Player* &character) = 0;

    bool IsActive() const override { return active; }

    Rectangle getHitbox() const override {
        return GameObject::getHitbox();
    }

    void readRectAnimation(const std::string filePath, Texture2D &sheet);
    void adaptCollision(ICollidable* other) override;
    virtual bool isSpecial() const {return true;}
    virtual void adaptCollision(const Rectangle &other);

    virtual void update(float deltaTime){
        GameObject::update(deltaTime);

        if(activeAnimation)
            activeAnimation->update(deltaTime);
    }

    void render() override;
};

class MushroomPowerUp : public PowerUp {
public:
    MushroomPowerUp(Vector2 pos) : PowerUp(PowerUpType::MUSHROOM, pos) {
        velocity.x = 35.0f;
    }
    void applyEffect(Player* &character) override;
    void update(float deltaTime) override;
};


class FireFlowerPowerUp : public PowerUp {
public:
    FireFlowerPowerUp(Vector2 pos) : PowerUp(PowerUpType::FIRE_FLOWER, pos) {
        readRectAnimation("../assets/animation/fireflower.txt", Images::textures["items1.png"]);
    }

    void applyEffect(Player* &character) override;
    void update(float deltaTime) override;
};


class StarPowerUp :public PowerUp {
private:
    const float bounceDamp = 0.4f;
    const float e = 1.0f;
    const float h_bounce = 50.0f;

    Vector2 reflect(const Vector2& v, const Vector2& n) {
        float dot = v.x*n.x + v.y*n.y;

        return { v.x - (1 + e) * dot * n.x,
                v.y - (1 + e) * dot * n.y };
    }
public:
    StarPowerUp(Vector2 pos) : PowerUp(PowerUpType::STAR, pos) {
        velocity.x = 70.0f;
        readRectAnimation("../assets/animation/star.txt", Images::textures["items.png"]);
    }

    void adaptCollision(const Rectangle &other) override;
    void update(float deltaTime) override;
    void applyEffect(Player* &character) override;
};


class NormalMushroomPowerUp : public PowerUp{
public:

    NormalMushroomPowerUp(Vector2 pos) : PowerUp(PowerUpType::NORMAL_MUSHROOM, pos){
         velocity.x = 35.0f;
    }

    bool isSpecial() const {return false;}
    void applyEffect(Player* &character) override;
    void update(float deltaTime) override;
};
