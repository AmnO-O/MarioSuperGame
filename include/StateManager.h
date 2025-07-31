#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <stack>
#include <memory>
#include <iostream>


class MenuState;
class StateManager;

class MenuState
{
    public:

        virtual ~MenuState() = default;

        virtual void update(float deltaTime) = 0;
        virtual void render() = 0;
};

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