#include "Character/PowerUp.h"
#include "Character/Character.h"


void PowerUp::update(float deltaTime, Character *&player) {
    if(!active || CheckCollisionRecs(hitbox, player ->getHitbox()) == 0) return; 

    active = false; 
}

void PowerUp::render(){

}