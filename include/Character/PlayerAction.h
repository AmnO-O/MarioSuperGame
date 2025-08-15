#pragma once
#include <memory>
#include <queue>
#include "Animation/LerpMover.h"
#include <iostream>

class Player; 
class PlayerMovement; 

class IAction {
public:
    virtual void execute(Player *player, PlayerMovement* movement, float deltaTime) = 0;
    virtual bool isFinished(Player *player, PlayerMovement* movement) const = 0;
    virtual void printData(std::ostream &fout) const {}

    virtual ~IAction() = default;
};

class SetPositionAction : public IAction{
    Vector2 position; 
    bool facingRight; 
    float currentTime = 0; 
    float timeShow;

    void printData(std::ostream &fout) const override{
        fout << "SetPositionAction " << position.x << " " << position.y << " " << facingRight << " " << timeShow << "\n";
    } 
public: 
    SetPositionAction(Vector2 pos, bool facingRight_, float timeShow_); 
    void execute(Player *player, PlayerMovement* movement, float deltaTime) override; 
    bool isFinished(Player *player, PlayerMovement* movement) const override; 
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

    float forceVelocity_x; 
    float forceVelocity_y; 

    void printData(std::ostream &fout) const override{
        fout << "JumpAction " << forceVelocity_x << ' ' << forceVelocity_y << "\n"; 
    }
public:
    JumpAction(float forceVelocity_x, float forceVelocity_y) : forceVelocity_x(forceVelocity_x), forceVelocity_y(forceVelocity_y){}
    void execute(Player *player, PlayerMovement* movement, float deltaTime) override; 
    bool isFinished(Player *player, PlayerMovement* movement) const override; 
};

class ClimbAction : public IAction {
    float currentTime = 0; 
    float targetY;
    LerpMover lerpMover; 
    float timeAction; 

    void printData(std::ostream &fout) const override{
        fout << "ClimbAction " << targetY << ' ' << timeAction << "\n"; 
    }
public:
    ClimbAction(float targetY_, float timeAction_) : targetY(targetY_), timeAction(timeAction_){}
    void execute(Player *player, PlayerMovement* movement, float deltaTime) override; 
    bool isFinished(Player *player, PlayerMovement* movement) const override; 
};

class TopEnterAction : public IAction{
    float currentTime = 0; 
    LerpMover lerpMover; 

    
    void printData(std::ostream &fout) const override{
        fout << "TopEnterAction \n";
    }
public: 
    TopEnterAction(){}; 
    void execute(Player *player, PlayerMovement* movement, float deltaTime) override; 
    bool isFinished(Player *player, PlayerMovement* movement) const override; 
}; 

class HorizontalEnterAction : public IAction {
    float currentTime = 0; 
    LerpMover lerpMover; 
    void printData(std::ostream &fout) const override{
        fout << "HorizontalEnterAction \n";
    }
public: 
    HorizontalEnterAction(){}; 
    void execute(Player *player, PlayerMovement* movement, float deltaTime) override; 
    bool isFinished(Player *player, PlayerMovement* movement) const override; 
};

class PopupAction : public IAction{
    float currentTime = 0; 
    LerpMover lerpMover;
    void printData(std::ostream &fout) const override{
        fout << "PopupAction \n";
    }
 public: 
    PopupAction(){}; 
    void execute(Player *player, PlayerMovement* movement, float deltaTime) override; 
    bool isFinished(Player *player, PlayerMovement* movement) const override; 
};


class PlayerActionManager {
private:
    std::deque<std::unique_ptr<IAction>> actionQueue;
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
    bool isEmpty() const { return actionQueue.empty(); }

    void printData(std::ostream &fout) const{
        fout << "PlayerActionManager " << actionQueue.size() << '\n'; 
        for(const auto & action : actionQueue){
            action->printData(fout); 
        }
    }

    void loadData(std::istream &fin){
        std::string actionType;

        int action_size; 
        fin >> action_size; 

        for(int i = 0; i < action_size; i ++){
            fin >> actionType; 
            
            if (actionType == "SetPositionAction") {
                Vector2 pos;
                bool facingRight;
                float timeShow;
                fin >> pos.x >> pos.y >> facingRight >> timeShow;
                addAction(std::make_unique<SetPositionAction>(pos, facingRight, timeShow));
            } else if (actionType == "RunAction") {
                float targetX;
                fin >> targetX;
                addAction(std::make_unique<RunAction>(targetX));
            } else if (actionType == "JumpAction") {
                float forceVelocity_x, forceVelocity_y;
                fin >> forceVelocity_x >> forceVelocity_y;
                addAction(std::make_unique<JumpAction>(forceVelocity_x, forceVelocity_y));
            } else if (actionType == "ClimbAction") {
                float targetY, timeAction;
                fin >> targetY >> timeAction;
                addAction(std::make_unique<ClimbAction>(targetY, timeAction));
            } else if (actionType == "TopEnterAction") {
                addAction(std::make_unique<TopEnterAction>());
            } else if (actionType == "HorizontalEnterAction") {
                addAction(std::make_unique<HorizontalEnterAction>());
            } else if (actionType == "PopupAction") {
                addAction(std::make_unique<PopupAction>());
            }
        }
    }
};
