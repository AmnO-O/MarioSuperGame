#pragma once
#include <memory>
#include <queue>
#include "Animation/LerpMover.h"

class Player; 
class PlayerMovement; 

class IAction {
public:
    virtual void execute(Player *player, PlayerMovement* movement, float deltaTime) = 0;
    virtual bool isFinished(Player *player, PlayerMovement* movement) const = 0;
    virtual ~IAction() = default;
};


class RunAction : public IAction {
    float targetX;
    float currentTime = 0; 
    LerpMover lerpMover; 
public:
    RunAction(float target); 
    void execute(Player *player, PlayerMovement* movement, float deltaTime) override; 
    bool isFinished(Player *player, PlayerMovement* movement) const override; 
};

class JumpAction : public IAction {
    float currentTime = 0; 
public:
    void execute(Player *player, PlayerMovement* movement, float deltaTime) override; 
    bool isFinished(Player *player, PlayerMovement* movement) const override; 
};

class TopEnterAction : public IAction{
    float currentTime = 0; 
    LerpMover lerpMover; 
public: 
    TopEnterAction(){}; 
    void execute(Player *player, PlayerMovement* movement, float deltaTime) override; 
    bool isFinished(Player *player, PlayerMovement* movement) const override; 
}; 

class HorizontalEnterAction : public IAction {
    float currentTime = 0; 
    LerpMover lerpMover; 
public: 
    HorizontalEnterAction(){}; 
    void execute(Player *player, PlayerMovement* movement, float deltaTime) override; 
    bool isFinished(Player *player, PlayerMovement* movement) const override; 
};

class PopupAction : public IAction{
    float currentTime = 0; 
    LerpMover lerpMover;
 public: 
    PopupAction(){}; 
    void execute(Player *player, PlayerMovement* movement, float deltaTime) override; 
    bool isFinished(Player *player, PlayerMovement* movement) const override; 
};


class PlayerActionManager {
private:
    std::queue<std::unique_ptr<IAction>> actionQueue;
    Player* player;
public:
    PlayerActionManager(){player = nullptr;}
    PlayerActionManager(Player* player_); 
    void setPlayer(Player *player_) {this->player = player_;}
    bool doneAction() {return actionQueue.empty();}
    void addAction(std::unique_ptr<IAction> action);
    void skipCurrentAction();
    void update(float deltaTime);
    void resetAll(); 
};
