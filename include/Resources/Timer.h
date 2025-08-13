#ifndef TIMER_H
#define TIMER_H

#include <string>
#include <cstdio>
#include <raylib.h>
#include <cmath>


class Timer
{
    private:

        Timer() = default;
        Timer(const Timer&) = delete;
        Timer& operator=(const Timer&) = delete;
 
    public:

        float remaining;
        Color time_color;
        bool warning_played = false;
        bool finalUpdatePlayed = false;
        
        static Timer& getInstance();
        void setup(float seconds);
        void update(float deltaTime);
        void finalUpdate(float deltaTime);
};

#endif