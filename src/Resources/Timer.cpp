#include "Resources/Timer.h"
#include "Resources/SoundManager.h"
#include "Resources/StateManager.h"
#include "States/GameOverMenu.h"

Timer& Timer::getInstance()
{
    static Timer instance;
    return instance;
}

void Timer::setup(float seconds)
{
    remaining = seconds;
    time_color = WHITE;
    warning_played = false;
}

void Timer::update(float deltaTime)
{
    if (remaining > 0.0f && !SoundManager::getInstance().death_played)
    {
        remaining -= deltaTime;
        if (remaining < 0.0f)
            remaining = 0.0f;
    }

    if (remaining <= 11.0f && !warning_played)
    {
        time_color = RED;
        PlaySound(SoundManager::getInstance().warningSound);
        warning_played = true;
    }   
}