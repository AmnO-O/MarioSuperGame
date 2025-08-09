#include "Resources/Timer.h"
#include "Resources/SoundManager.h"

Timer& Timer::getInstance()
{
    static Timer instance;
    return instance;
}

void Timer::setup(float seconds)
{
    remaining = seconds;
    time_color = WHITE;
}

void Timer::update(float deltaTime)
{
    if (remaining > 0.0f && !SoundManager::getInstance().death_played)
    {
        remaining -= deltaTime;
        if (remaining < 0.0f)
            remaining = 0.0f;
    }

    if (remaining <= 6.0f)
    {
        time_color = RED;
    }   
}