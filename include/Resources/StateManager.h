#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <stack>
#include <memory>
#include <iostream>

class StateManager;

class GameState
{
    public:

        virtual ~GameState() = default;

        virtual void processInput(StateManager& stateManager) = 0;
        virtual void update(float deltaTime) = 0;
        virtual void render() = 0;
};

class StateManager 
{
    private:

        std::stack<std::unique_ptr<GameState>> stateStack;

    public:

        StateManager() = default;
        ~StateManager() = default;

        void pushState(std::unique_ptr<GameState> newState);
        void popState();
        GameState* getCurrentState();
        void update(float deltaTime);
        void render();
        
};



#endif