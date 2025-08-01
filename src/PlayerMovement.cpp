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
                                    Character* player) {
    Rectangle body  = bodyBox();
    Rectangle feet  = footBox();
    Rectangle hit   = other->getHitbox();

    // Check overlap
    float left   = (body.x + body.width)  - hit.x;
    float right  = (hit.x + hit.width)    - body.x;
    float top    = (body.y + body.height) - hit.y;
    float bottom = (hit.y + hit.height)   - body.y;
    if (left <= 0 || right <= 0 || top <= 0 || bottom <= 0)
        return;

    // Determine minimal penetration direction
    float minPen = left;
    enum Dir { LEFT, RIGHT, TOP, BOTTOM } dir = LEFT;
    if (right < minPen)  { minPen = right;  dir = RIGHT; }
    if (top < minPen)    { minPen = top;    dir = TOP; }
    if (bottom < minPen) { minPen = bottom; dir = BOTTOM; }

    const float EPS = 0.01f;
    switch (dir) {
        case LEFT:
            if (std::fabs(left) > EPS) {
                position.x -= left;
                velocity.x = 0;
            }
            break;
        case RIGHT:
            if (std::fabs(right) > EPS) {
                position.x += right;
                velocity.x = 0;
            }
            break;
        case TOP:
            // only when falling or stationary
            if (velocity.y >= 0) {
                // compute feet overlap
                float fOverlap = (feet.y + feet.height) - hit.y;
                if (fOverlap > EPS) {
                    position.y -= fOverlap;
                    velocity.y = 0;
                    delete Mstate;
                    if (std::fabs(velocity.x) > EPS) Mstate = new RunState();
                    else                              Mstate = new StandState();
                    player->setGroundLevel(hit.y);
                }
            }
            break;
        case BOTTOM:
            // hitting ceiling
            if (velocity.y < 0 && std::fabs(bottom) > EPS) {
                position.y += bottom;
                velocity.y = 100.0f;
            }
            break;
    }
}



void PlayerMovement::update(float deltaTime, IShapeState *&Sstate, IMoveState  *&Mstate){
	currentTime += deltaTime; 
	// std::cout << "Movement:" << groundLevel << '\n'; 


	bool pressingLeft = IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT);
	bool pressingRight = IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT) ;
	
	bool isClickedSpace = IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W); 
	bool pressingSpace = IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_UP) || IsKeyDown(KEY_W);

	bool pressingCrounch = IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN) || IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_DOWN); 
	
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

	velocity.x = std::min(velocity.x, 150.0f);
	velocity.x = std::max(velocity.x, -150.0f);

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