#pragma once
#include "Character/Global.h"
#include "Object/GameObject.h"
#include "Animation/Appearance.h"
#include "Observer/ICollidable.h"

class Character;

class PowerUp : public GameObject, public ICollidable{
protected: 
    Texture2D &tex;
    Rectangle srcRect;
    PowerUpType type; 
    AppearanceAnimation ani;
    bool hasSpawned = false;
public: 
    PowerUp(PowerUpType t, Texture2D &tex, Rectangle src, Rectangle block): srcRect(src), type(t), GameObject(), tex(tex), ani(tex, block, 0.8f, src.height, 1.0f) {
        ani.addRect(src);
        Vector2 pos = ani.getPosition();
        hitbox = {pos.x, pos.y, srcRect.width, srcRect.height}; 
        position = {pos.x, pos.y - srcRect.height};
        setGroundLevel(block.y);
    }

    Rectangle getHitbox() const override { return hitbox; }
    bool IsActive() const override { return active; } 

    virtual void applyEffect(Character* &character) = 0;
    void adaptCollision(ICollidable* other);
    void isHitBelow() override {}
    void render() override;
    void update(float delta) override;
}; 

class MushroomPowerUp : public PowerUp {
public: 
    MushroomPowerUp(Texture2D &tex, Rectangle src, Rectangle block) : PowerUp(PowerUpType::MUSHROOM, tex, src, block) {velocity.x = -30.0f;};
    void applyEffect(Character* &character) override; 
};


class FireFlowerPowerUp : public PowerUp {
public:
    FireFlowerPowerUp(Texture2D &tex, Rectangle src, Rectangle block) : PowerUp(PowerUpType::FIRE_FLOWER, tex, src, block) {};
    void applyEffect(Character* &character) override; 
};


class StarPowerUp :public PowerUp {
public: 
    StarPowerUp(Texture2D &tex, Rectangle src, Rectangle block) : PowerUp(PowerUpType::STAR, tex, src, block) {velocity.x = -50.0f;}; 
    void applyEffect(Character* &character) override; 
};

