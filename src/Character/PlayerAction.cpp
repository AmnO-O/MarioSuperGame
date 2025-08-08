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
    if (actionQueue.empty()) return;

    auto& currentAction = actionQueue.front();
    currentAction->execute(player, player->movement, deltaTime);

    if (currentAction->isFinished(player, player->movement)) {
        actionQueue.pop();
    }
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
    }
    currentTime += deltaTime; 
}

bool EnterAction::isFinished(Player *player, PlayerMovement* movement) const {
    return true; 
}