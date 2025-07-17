#include "Character/PowerUp.h"



void PowerUp::update(float deltaTime, Character *player) {
    if(!active || CheckCollisionRecs(hitbox, player ->getHitbox()) == 0) return; 

    switch(type) {
        case PowerUpType::MUSHROOM:
            player -> transformToTransformed();
            break;
        case PowerUpType::FIRE_FLOWER:
            player -> transformToFire();
            break;
    }

    active = false; 
}

void PowerUp::render(){

}