#pragma once
#include "Character/Global.h"
#include "GameObject.h"
#include "Animation/Animation.h"
#include "Observer/ICollidable.h"
#include <iostream>
class Player;

class PowerUp : public GameObject, public ICollidable {
protected:
    PowerUpType type;
    AnimationManager *activeAnimation;
    AppearanceAnimation *ani;
    bool hasSpawned = false;

public:
    PowerUp(PowerUpType t, Rectangle block)
        : type(t), GameObject(), activeAnimation(nullptr), ani(nullptr) {
            setGroundLevel(block.y);
    }

    virtual ~PowerUp() { delete activeAnimation;  delete ani;}

    virtual void applyEffect(Player* &character) = 0;

    bool IsActive() const override { return active; }

    Rectangle getHitbox() const override {
        return hasSpawned ? hitbox : ani->getHitBox();
    }

    void isHitBelow(ICollidable* block) override {
        Rectangle rect = block->getHitbox();

        hitbox.y = rect.y - hitbox.height;

        velocity.y = -200.0f;

        float playerCenterX = hitbox.x + hitbox.width  * 0.5f;
        float  blockCenterX = rect.x    + rect.width * 0.5f;


        if (playerCenterX > blockCenterX) {
            velocity.x = fabs(velocity.x);
        } else {
            velocity.x = - fabs(velocity.x); 
        }
    }


    void readRectAnimation(const std::string filePath, Texture2D &sheet);
    void adaptCollision(ICollidable* other) override;
    virtual bool isSpecial() const {return true;}
    virtual void adaptCollision(const Rectangle &other);
    virtual void update(float deltaTime);
    void render() override;
};

class MushroomPowerUp : public PowerUp {
public:
    MushroomPowerUp(Rectangle block) : PowerUp(PowerUpType::MUSHROOM, block) {
        readRectAnimation("assets/animation/mushroom.txt", Images::textures["mushroom.png"]);
        ani->setBlockRec(block);
        velocity.x = 35.0f;
    }
    void applyEffect(Player* &character) override;
    void update(float deltaTime) override;
};


class FireFlowerPowerUp : public PowerUp {
public:
    FireFlowerPowerUp(Rectangle block) : PowerUp(PowerUpType::FIRE_FLOWER, block) {
        readRectAnimation("assets/animation/fireflower.txt", Images::textures["items1.png"]);
        ani->setBlockRec(block);
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
    StarPowerUp(Rectangle block) : PowerUp(PowerUpType::STAR, block) {
        velocity.x = 70.0f;

        readRectAnimation("assets/animation/star.txt", Images::textures["items.png"]);
        ani->setBlockRec(block);
    }

    void adaptCollision(const Rectangle &other) override;
    void update(float deltaTime) override;
    void applyEffect(Player* &character) override;
};


class NormalMushroomPowerUp : public PowerUp{
public:

    NormalMushroomPowerUp(Rectangle block) : PowerUp(PowerUpType::NORMAL_MUSHROOM, block){
        readRectAnimation("assets/animation/mushroom.txt", Images::textures["1upMushroom.png"]);
        ani->setBlockRec(block);
        velocity.x = 35.0f;
    }

    bool isSpecial() const {return false;}
    void applyEffect(Player* &character) override;
    void update(float deltaTime) override;
};
