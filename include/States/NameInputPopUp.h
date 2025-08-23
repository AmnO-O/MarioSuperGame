#pragma once
#include <iostream>
#include "Resources/StateManager.h"
#include "raylib.h"

class NameInputPopUp : public GameState {
private:
    static std::string playerName;
    bool isActive;
    bool isAnimating;
    float animationTimer;
    float popupScale;
    int blinkTimer;
    bool showCursor;
    int mapNumber;

    // UI Colors
    Color overlayColor = { 0, 0, 0, 150 };
    Color popupBg = { 45, 55, 85, 255 };
    Color popupBorder = { 255, 215, 0, 255 }; 
    Color titleColor = { 255, 215, 0, 255 };  
    Color textColor = { 255, 255, 255, 255 };  
    Color inputBg = { 30, 35, 55, 255 };
    Color inputBorder = { 100, 150, 255, 255 };
    Color buttonColor = { 50, 150, 50, 255 };
    Color buttonHover = { 70, 170, 70, 255 };

    Rectangle popupRect;
    Rectangle inputRect;
    Rectangle buttonRect;
    Vector2 titlePos;
    Vector2 subtitlePos;
    Vector2 inputTextPos;

    Font font; 
    
public: 
    NameInputPopUp(); 

    void show(int mapNum);
    void hide();
    bool getIsActive() const { return isActive; }
    static const  std::string getPlayerName() { return playerName; }
    int getMapNumber() const { return mapNumber; }
    void processInput() override;
    void update(float deltaTime) override;
    void render() override;
    ~NameInputPopUp();
}; 

