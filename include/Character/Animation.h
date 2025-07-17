#pragma once
#include "raylib.h"
#include <vector>

class SpriteAnimated{
private: 
    Texture2D sheet; 
    std::vector<Rectangle> frames;

    float currentTime; 
    float timeSwitch; 

    bool flipX; 
    int currentIndex; 
public: 
    SpriteAnimated() = default; 
    SpriteAnimated(Texture2D &t, bool flip): 
        sheet(t), currentTime(0.0f), timeSwitch(0.2f), 
        flipX(flip), currentIndex(0){}; 

    Vector2 getCurrentShape() const;
     
    void update(float deltaTime); 
    void render(); 
}; 