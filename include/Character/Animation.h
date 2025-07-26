#pragma once
#include "raylib.h"
#include <vector>

class AnimationManager{
private: 
    Texture2D sheet; 
    std::vector<Rectangle> frames;

    float currentTime; 
    float timeSwitch; 

    bool flipX; 
    int currentIndex; 

    bool isOnePeriod = false; 
public: 
    AnimationManager() = default; 
    AnimationManager(Texture2D &t, bool flip): 
        sheet(t), currentTime(0.0f), timeSwitch(0.2f), 
        flipX(flip), currentIndex(0){}; 

    Vector2 getCurrentShape() const;
    bool isOnePeriodPassed() const {return isOnePeriod;}
    void setTimeSwitch(float timeSwitch) {this -> timeSwitch = timeSwitch;}
    void addRect(const Rectangle& rect);   
    void update(float deltaTime); 
    void render(Vector2 position, bool flip = false); 
    void Draw(Vector2 position) const;
}; 