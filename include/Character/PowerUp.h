#pragma once
#include "Global.h"
#include "Character/Character.h"

class PowerUp{
protected: 
    PowerUpType type; 
    Vector2 position; 
    Vector2 velocity; 
    Rectangle hitbox; 

    bool active; 
    bool onGround; 
    
public: 
    PowerUp(PowerUpType t, Vector2 pos): type(t), position(pos), velocity({0, 0}),
    active(true), onGround(false){
        hitbox = {position.x, position.y, 16, 16}; 
    }

    void update(float deltaTime, Character *player); 
    bool isActive() const { return active; }
    void adaptCollision(const Rectangle& rect);

    Rectangle getHitbox() const { return hitbox;}
    void render();
}; 

class MushroomPowerUp : public PowerUp {
public: 
    MushroomPowerUp(Vector2 pos) : PowerUp(PowerUpType::MUSHROOM, pos) {};
};


class FireFlowerPowerUp : public PowerUp {
public:
    FireFlowerPowerUp(Vector2 pos) : PowerUp(PowerUpType::FIRE_FLOWER, pos) {};
};


class StarPowerUp :public PowerUp {
public: 
    StarPowerUp(Vector2 pos) : PowerUp(PowerUpType::STAR, pos) {}; 
};

