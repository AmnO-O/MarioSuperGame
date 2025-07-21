#include "Character/CharacterState.h"
#include <iostream>

IMoveState *StandState::update(MoveContext *player){
    if(player->isCrouch && player->isBig){
        player->currentTime = 0; 
        return new CrouchState(); 
    }

    if(player->velocity.x != 0) {
        player->currentTime = 0; 
        player->facingRight = (player->velocity.x > 0); 
        return new RunState(); 
    }

    return this; 
}

IMoveState *RunState::update(MoveContext *player){
    if(player->isCrouch && player->isBig){
        player->currentTime = 0; 
        return new CrouchState(); 
    }
    
    if(player->velocity.x  * player->force.x < 0){
        player->facingRight = (player->force.x >= 0);
        player->currentTime = 0;  
        return new SkidState(); 
    }

    if(player->velocity.x == 0 && player->force.x == 0)
        return new StandState(); 

    return this; 
}

IMoveState *SkidState::update(MoveContext *player){
    if(player->currentTime <= 0.2f) return this; 

    if(player->velocity.x < 0 && player->force.x > 0){
        player->facingRight = true; 
        player->currentTime = 0; 
        return new RunState(); 
    }

    if(player->velocity.x > 0 && player->force.x < 0){
        player->facingRight = false;
        player->currentTime = 0; 
 
        return new RunState(); 
    }

    if(player->velocity.x * player->force.x >= 0){
        player->currentTime = 0; 
        return new RunState(); 
    }

    if(player->velocity.x == 0){
        player->currentTime = 0; 
        return new StandState();
    } 

    
    return this; 
}

IMoveState *JumpState::update(MoveContext *player){
    if(player->position.y >= player->groundLevel - player->shape.y){
        player->velocity.y = 0; 
        player->position.y = player->groundLevel - player->shape.y; 
        return new StandState(); 
    }

    return this; 
}

IMoveState *CrouchState::update(MoveContext *player){
    if(player -> isBig == 0) 
        return new StandState();

    if(player->isCrouch == 0){
        if(player->velocity.y != 0){
            return new JumpState(); 
        }

        player->position.y = player->groundLevel - player->shape.y - 9; 

        if(player->velocity.x != 0)
            return new RunState();

        return new StandState(); 
    }

    if(this->isJumping() && player->position.y >= player->groundLevel - player->shape.y){
        player->velocity.y = 0; 
        player->position.y = player->groundLevel - player->shape.y; 
        this->changeIsJump();
        player->force = {0, 0}; 
    }

    return this; 
}


void StandState::update(float deltaTime) {

}

void RunState::update(float deltaTime){

}

void JumpState::update(float deltaTime){

}

void SkidState::update(float deltaTime){

}

void CrouchState::update(float deltaTime){

}