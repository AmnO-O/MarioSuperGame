#include "Resources/StateManager.h"
#include "States/World.h"

StateManager& StateManager::getInstance()
{
    static StateManager instance;
    return instance;
}

void StateManager::pushState(std::unique_ptr<GameState> newState)
{
    stateStack.push(std::move(newState));
}

void StateManager::popState()
{
    if (!stateStack.empty())
        stateStack.pop();
}

GameState* StateManager::getCurrentState()
{
    if (!stateStack.empty())
        return stateStack.top().get();
    
    return nullptr;
}

void StateManager::update(float deltaTime)
{
    GameState* currentState = getCurrentState();
    if (currentState)
        currentState->update(deltaTime);
}

void StateManager::render()
{
    GameState* currentState = getCurrentState();
    if (currentState)
        currentState->render();
}
