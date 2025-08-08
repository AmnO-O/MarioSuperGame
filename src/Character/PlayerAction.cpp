#include "Character/PlayerAction.h"
#include "Character/Character.h" 

PlayerActionManager::PlayerActionManager(Player* player_) : player(player_) {}

void PlayerActionManager::addAction(std::unique_ptr<IAction> action) {
    actionQueue.push(std::move(action));
}

void PlayerActionManager::skipCurrentAction(){
    if(!actionQueue.size()) return; 
    actionQueue.pop(); 
}

void PlayerActionManager::update(float deltaTime) {
    if(player == nullptr)
        throw GameException("Player is null at  PlayerActionManager::update");
    if (actionQueue.empty() || player == nullptr) return;

    auto& currentAction = actionQueue.front();
    currentAction->execute(player, player->movement, deltaTime);

    if (currentAction->isFinished(player, player->movement)) {
        actionQueue.pop();
    }
}

void PlayerActionManager::resetAll(){
    player->movement->unlockMovement(); 
    while(actionQueue.size()) actionQueue.pop();
}

RunAction::RunAction(float target) : targetX(target) {}

void RunAction::execute(Player *player, PlayerMovement* movement, float deltaTime) {

}

bool RunAction::isFinished(Player *player, PlayerMovement* movement) const {
    return true; 
}



void JumpAction::execute(Player *player, PlayerMovement* movement, float deltaTime) {

}

bool JumpAction::isFinished(Player *player, PlayerMovement* movement) const {
    return true; 
}


void EnterAction::execute(Player *player, PlayerMovement* movement, float deltaTime) {
    if(currentTime == 0){
        player->changeMstate(new EnterState()); 
        movement->lockMovement(); 
        Vector2 startPos = movement->getPosition(); 
        Vector2 endPos = {startPos.x, startPos.y + 30.0f};
        lerpMover.start(startPos, endPos, 2.0f); 
    }

    currentTime += deltaTime; 
    Vector2 nextPos = lerpMover.update(deltaTime); 
    movement->setPosition(nextPos); 
}

bool EnterAction::isFinished(Player *player, PlayerMovement* movement) const {
    return lerpMover.isDone(); 
}