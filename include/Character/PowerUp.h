#pragma once
#include "Global.h"
#include "GameObject.h"

class Character;

class PowerUp : public GameObject{
protected: 
    PowerUpType type; 
public: 
    PowerUp(PowerUpType t, Vector2 pos): type(t), GameObject(pos, {0, 0}){
        hitbox = {pos.x, pos.y, 16, 16}; 
    }

    virtual void applyEffect(Character* &character) = 0;

    bool isActive() const { return active; }
    void adaptCollision(const Rectangle& rect);
    void render() override;
}; 

class MushroomPowerUp : public PowerUp {
public: 
    MushroomPowerUp(Vector2 pos) : PowerUp(PowerUpType::MUSHROOM, pos) {velocity.x = -30.0f;};
    void applyEffect(Character* &character) override; 
};


class FireFlowerPowerUp : public PowerUp {
public:
    FireFlowerPowerUp(Vector2 pos) : PowerUp(PowerUpType::FIRE_FLOWER, pos) {};
    void applyEffect(Character* &character) override; 
};


class StarPowerUp :public PowerUp {
public: 
    StarPowerUp(Vector2 pos) : PowerUp(PowerUpType::STAR, pos) {velocity.x = -50.0f;}; 
    void applyEffect(Character* &character) override; 
};

