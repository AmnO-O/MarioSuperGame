#pragma once
#include "raylib.h"

class LerpMover{
private:
    Vector2 startPos;
    Vector2 endPos;
    float   duration = 2.0f;    
    float   elapsed = 0;   
    bool    active  = false;
public: 
    void start(const Vector2& from, const Vector2& to, float timeSeconds) {
        startPos = from;
        endPos   = to;
        duration = timeSeconds > 0 ? timeSeconds : 0.001f;
        elapsed  = 0;
        active   = true;
    }

    Vector2 update(float deltaTime) {
        if (!active) return endPos;

        elapsed += deltaTime;
        float t = elapsed / duration;
        if (t >= 1.0f) {
            t = 1.0f;
            active = false;
        }

        return {
            startPos.x + t * (endPos.x - startPos.x),
            startPos.y + t * (endPos.y - startPos.y)
        };
    }

    bool isDone() const { return !active; }
}; 
