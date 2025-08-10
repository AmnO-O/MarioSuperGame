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

        virtual void processInput() = 0;
        virtual void update(float deltaTime) = 0;
        virtual void render() = 0;
};

class StateManager 
{
    private:

        std::stack<std::unique_ptr<GameState>> stateStack;
        
        StateManager() = default; 
        StateManager(const StateManager&) = delete;
        StateManager& operator=(const StateManager&) = delete;

    public:
        
        static StateManager& getInstance();
        void pushState(std::unique_ptr<GameState> newState);
        void popState();
        GameState* getCurrentState();
        void update(float deltaTime);
        void render();
        
};



#endif