	#include "Character/PlayerMovement.h"
	#include "Character/CharacterState.h"
	#include <iostream>

void PlayerMovement::update(float deltaTime, IShapeState *&Sstate, IMoveState  *&Mstate){
	currentTime += deltaTime; 

	bool pressingLeft = IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT);
	bool pressingRight = IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT) ;
	
	bool isClickedSpace = IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W); 
	bool pressingSpace = IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_UP) || IsKeyDown(KEY_W);

	bool pressingCrounch = IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN); 
	

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
		velocity.x *= 0.8f; 
		if (velocity.x < 0)
			velocity.x = std::min(velocity.x + 50 * deltaTime, 0.0f);
		else if (velocity.x > 0)
			velocity.x = std::max(velocity.x - 50 * deltaTime, 0.0f);
	}

	if(isClickedSpace && Mstate->isJumping() == false){
		forceY += stats->jumpInitialVelocity; 
		currentTime = 0; 

		delete Mstate; 
		Mstate = new JumpState(); 
	}
	else if(pressingSpace && Mstate->isJumping() && currentTime <= stats->maxJumpTime){
		forceY += stats->jumpHoldAcceleration; 
	}else if(Mstate -> isJumping() == false){
		forceY -= 980; 
	}
	
	velocity.x += forceX * deltaTime;
	velocity.y += forceY * deltaTime;

	velocity.x = std::min(velocity.x, 150.0f);
	velocity.x = std::max(velocity.x, -150.0f);


	position.x += velocity.x * deltaTime;
	position.y += velocity.y * deltaTime;

	if (position.x < 0.0f)
		position.x = 0.0f;

	Vector2 force = {forceX, forceY}; 

	MoveContext currentContext = {position, velocity, force, facingRight, groundLevel,currentTime, Sstate->canBreakBrick()}; 
	IMoveState *nextState = Mstate->update(&currentContext); 

	if(nextState != Mstate){
		delete Mstate; 
		Mstate = nextState; 
	}
}