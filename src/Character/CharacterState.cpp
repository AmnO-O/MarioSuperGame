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

IMoveState *ShootState::update(MoveContext *player){
    if(this->currentTime >= 0.1){
        if( player->position.y < player->groundLevel - player->shape.y){
            return (new JumpState()) -> update(player); 
        }else{
            player->position.y = player->groundLevel - player->shape.y; 
            player->velocity.y = 0; 

            if(player->velocity.x != 0) 
                return (new RunState()) -> update(player); 
            return (new StandState()) -> update(player); 
        }
    }

    if(this->isJumping() == false && player->position.y < player->groundLevel - player->shape.y){
        this->changeIsJump(); 
    }else if(player->position.y >= player->groundLevel - player->shape.y){
        player->position.y = player->groundLevel - player->shape.y; 
        player->velocity.y = 0.f; 
        isJump = false; 
    }

    return this; 
}