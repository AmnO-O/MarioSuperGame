#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <stack>
#include <memory>
#include "MenuState.h"

class StateManager 
{
    private:

        std::stack<std::unique_ptr<MenuState>> stateStack;

    public:

        StateManager() = default;
        ~StateManager() = default;

        void pushState(std::unique_ptr<MenuState> newState);
        void popState();
        MenuState* getCurrentState();
        void update(float deltaTime);
        void render();
        
};

#endif