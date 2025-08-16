#include "Character/PlayerAction.h"
#include "Character/Character.h" 

PlayerActionManager::PlayerActionManager(Player* player_) : player(player_) {}

void PlayerActionManager::addAction(std::unique_ptr<IAction> action) {
    actionQueue.push_back(std::move(action));
}

void PlayerActionManager::skipCurrentAction(){
    if(!actionQueue.size()) return; 
    actionQueue.pop_front(); 
}

void PlayerActionManager::update(float deltaTime) {
    if(player == nullptr)
        throw GameException("Player is null at  PlayerActionManager::update");
    if (actionQueue.empty() || player == nullptr) return;

    auto& currentAction = actionQueue.front();
    
    if (currentAction == nullptr) {
        actionQueue.pop_front();
        return;
    }
    
    currentAction->execute(player, player->movement, deltaTime);

    if (currentAction->isFinished(player, player->movement)) {
        actionQueue.pop_front();
    }

    if(doneAction()){
        player->movement->unlockMovement();
        player->movement->unlockKeyboardInput();
    }
}

void PlayerActionManager::resetAll(){
    player->movement->unlockMovement(); 
    player->movement->unlockKeyboardInput(); 
    while(actionQueue.size()) actionQueue.pop_front();
}


SetPositionAction::SetPositionAction(Vector2 pos, bool facingRight_, float timeShow_) : 
    position(pos), facingRight(facingRight_), timeShow(timeShow_) {currentTime = 0.0f;}

void SetPositionAction::execute(Player *player, PlayerMovement* movement, float deltaTime) {
    if(currentTime == 0){
        player->changeMstate(new ClimbState());
 
        movement->lockMovement(); 
        movement->setPosition(position);
        movement->setFacingRight(facingRight);

    }

    currentTime += deltaTime; 
}

bool SetPositionAction::isFinished(Player *player, PlayerMovement* movement) const {
    return currentTime >= timeShow; 
}



RunAction::RunAction(float target) : targetX(target) {}

void RunAction::execute(Player *player, PlayerMovement* movement, float deltaTime) {
    if(currentTime == 0){
        player->changeMstate(new RunState()); 
        movement->lockMovement(); 
        Vector2 startPos = movement->getPosition(); 
        Vector2 endPos = {targetX, startPos.y};
        lerpMover.start(startPos, endPos, 2.0f); 
    }

    currentTime += deltaTime; 
}

bool RunAction::isFinished(Player *player, PlayerMovement* movement) const {
    return true; 
}



void JumpAction::execute(Player *player, PlayerMovement* movement, float deltaTime) {
    if(currentTime == 0){
        player->changeMstate(new JumpState()); 
        movement->setVelocityX(forceVelocity_x); 
        movement->setVelocityY(forceVelocity_y); 
        movement->unlockMovement();
        movement->lockKeyboardInput(); 
    }
    
    currentTime += deltaTime;
}

bool JumpAction::isFinished(Player *player, PlayerMovement* movement) const {
    return movement->getVelocity().y == 0 && movement->getVelocity().x == 0; 
}



void ClimbAction::execute(Player *player, PlayerMovement* movement, float deltaTime) {
    if(currentTime == 0){
        player->changeMstate(new ClimbState()); 
        movement->lockMovement(); 
        Vector2 startPos = movement->getPosition(); 
        Vector2 endPos = {startPos.x, targetY};
        lerpMover.start(startPos, endPos, 1.0f); 
    }

    currentTime += deltaTime; 
    Vector2 nextPos = lerpMover.update(deltaTime); 
    movement->setPosition(nextPos); 
}

bool ClimbAction::isFinished(Player *player, PlayerMovement* movement) const {
    return lerpMover.isDone() && timeAction <= currentTime; 
}




void TopEnterAction::execute(Player *player, PlayerMovement* movement, float deltaTime) {
    if(currentTime == 0){
        player->changeMstate(new EnterState()); 
        movement->lockMovement(); 
        Vector2 startPos = movement->getPosition(); 
        Vector2 endPos = {startPos.x, startPos.y + 20.0f};
        lerpMover.start(startPos, endPos, 2.0f); 
    }
    
    currentTime += deltaTime; 
    Vector2 nextPos = lerpMover.update(deltaTime);
    movement->setPosition(nextPos);

}

bool TopEnterAction::isFinished(Player *player, PlayerMovement* movement) const {
    return lerpMover.isDone(); 
}



void HorizontalEnterAction::execute(Player *player, PlayerMovement* movement, float deltaTime) {
    if(currentTime == 0){
        player->changeMstate(new StandState()); 
        movement->lockMovement(); 
        Vector2 startPos = movement->getPosition(); 
        Vector2 endPos = {startPos.x + 14.0f, startPos.y};
        lerpMover.start(startPos, endPos, 1.5f); 
    }

    currentTime += deltaTime; 
    Vector2 nextPos = lerpMover.update(deltaTime); 
    movement->setPosition(nextPos); 
}

bool HorizontalEnterAction::isFinished(Player *player, PlayerMovement* movement) const {
    return lerpMover.isDone(); 
}


void PopupAction::execute(Player *player, PlayerMovement* movement, float deltaTime) {
    if(currentTime == 0){
        player->changeMstate(new StandState()); 
        movement->lockMovement(); 
        Vector2 startPos = movement->getPosition(); 
        Vector2 endPos = {startPos.x, startPos.y - player->getShape().y};
        lerpMover.start(startPos, endPos, 1.0f); 
    }

    currentTime += deltaTime; 
    Vector2 nextPos = lerpMover.update(deltaTime); 
    movement->setPosition(nextPos); 
}

bool PopupAction::isFinished(Player *player, PlayerMovement* movement) const {
    return lerpMover.isDone(); 
}

