#include "StateManager.h"

void StateManager::pushState(std::unique_ptr<MenuState> newState)
{
    stateStack.push(std::move(newState));
}

void StateManager::popState()
{
    if (!stateStack.empty())
        stateStack.pop();
}

MenuState* StateManager::getCurrentState()
{
    if (!stateStack.empty())
        return stateStack.top().get();
    
    return nullptr;
}

void StateManager::update(float deltaTime)
{
    MenuState* currentState = getCurrentState();
    if (currentState)
        currentState->update(deltaTime);
}

void StateManager::render()
{
    MenuState* currentState = getCurrentState();
    if (currentState)
        currentState->render();
}
