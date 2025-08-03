#include "Character/PlayerMovement.h"
#include "Character/CharacterState.h"
#include "Character/Character.h"
#include <iostream>
#include "Exceptions.h"
#include <cassert>
#include <cmath>

void PlayerMovement::setOnGround(){
	position.y = groundLevel - shape.y; 
	velocity.y = 0; 
}

void PlayerMovement::setGroundLevel(float groundLevel_){
	 this->groundLevel = groundLevel_;

	 if(groundLevel - shape.y <= position.y){
		position.y = groundLevel - shape.y; 
		velocity.y = 0; 
	 }
}

void PlayerMovement::adaptCollision(ICollidable* other,
                                    IMoveState*& Mstate,
                                    Player* player) {
	Rectangle rect = other->getHitbox();

	float penLeft = (position.x + shape.x) - rect.x; 
	float penRight = (rect.x + rect.width) - position.x;
	float penX = penLeft < penRight ? -penLeft : penRight; 

	float penTop = (position.y + shape.y) - rect.y;
	float penBot = (rect.y + rect.height) - position.y;
	float penY = penTop < penBot ? -penTop : penBot;

	if (std::fabs(penX) < std::fabs(penY)) {
		position.x += penX;
		velocity.x = 0; 
	}
	else {
		position.y += penY; 
		velocity.y = 0; 
		if (penY < 0) {
            if (Mstate->isJumping()) {
                delete Mstate;
                if(velocity.x != 0) 
					Mstate = new RunState();
				else
					Mstate = new StandState(); 
            }

            player->setGroundLevel(rect.y);
			player->setOnGround(); 
		}
	}
}


void PlayerMovement::update(float deltaTime, IShapeState *&Sstate, IMoveState  *&Mstate){
	currentTime += deltaTime; 


	bool pressingLeft = IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT);
	bool pressingRight = IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT) ;
	
	bool isClickedSpace = IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W); 
	bool pressingSpace = IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_UP) || IsKeyDown(KEY_W);

	bool pressingCrounch = IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN) || IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_DOWN); 

	if(disableUpdate == true){
		pressingLeft = pressingRight = isClickedSpace = pressingSpace = pressingCrounch = false; 
		velocity.y += 980 * deltaTime;
        position.y += velocity.y * deltaTime;

		return ; 
	}
	
	float forceX = 0;
	float forceY = 980;

	if (pressingLeft) {
		facingRight = false; 
		forceX -= stats->runSpeed; 
	}
	else if (pressingRight) {
		facingRight = true; 
		forceX += stats->runSpeed; 
	}
	else {

		if (velocity.x < 0)
			velocity.x = std::min(velocity.x + 150 * deltaTime, 0.0f);
		else if (velocity.x > 0)
			velocity.x = std::max(velocity.x - 150 * deltaTime, 0.0f);

	}

	if(isClickedSpace && Mstate->isJumping() == false){
		forceY += stats->jumpInitialVelocity; 
		currentTime = 0; 

		if((pressingCrounch == false || Sstate->canBreakBrick() == false)){
			delete Mstate; 
			Mstate = new JumpState(); 
		}else{
			Mstate->changeIsJump(); 
		}
	}
	else if(pressingSpace && Mstate->isJumping() && currentTime <= stats->maxJumpTime){
		forceY += stats->jumpHoldAcceleration; 
	}else if(Mstate -> isJumping() == false){
		forceY -= 980;
	}

	if(Mstate->getMoveState() == "CROUCHING"){
		forceX = 0; 
		if(Mstate->isJumping() == false && velocity.y == 0){
			position.y = groundLevel - shape.y; 
		}
	}

	
	velocity.x += forceX * deltaTime;
	velocity.y += forceY * deltaTime;

	velocity.x = std::min(velocity.x, 200.0f);
	velocity.x = std::max(velocity.x, -200.0f);

	position.x += velocity.x * deltaTime;
	position.y += velocity.y * deltaTime;

	if (position.x < 0.0f)
		position.x = 0.0f;


	Vector2 force = {forceX, forceY}; 
	MoveContext currentContext = {position, velocity, force, shape, facingRight, groundLevel, currentTime, pressingCrounch, Sstate->canBreakBrick()}; 

	assert(Mstate != nullptr); 
	assert(Sstate != nullptr); 


	IMoveState *nextState = Mstate->update(&currentContext); 

	if(nextState != Mstate){
		delete Mstate; 
		Mstate = nextState; 
	}

}