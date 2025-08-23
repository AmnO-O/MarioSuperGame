#include "States/NameInputPopUp.h"
#include "States/SubMenu.h"
#include <string>

std::string NameInputPopUp::playerName = "";

NameInputPopUp::NameInputPopUp(){
    isActive = false;
    isAnimating = false;
    animationTimer = 0.0f;
    popupScale = 0.0f;
    blinkTimer = 0;
    showCursor = true;
    mapNumber = 1;

    float popupWidth = 600;
    float popupHeight = 400;
    popupRect = { (1600 - popupWidth) / 2, (900 - popupHeight) / 2, popupWidth, popupHeight };

    inputRect = { popupRect.x + 50, popupRect.y + 200, popupRect.width - 100, 60 };
    buttonRect = { popupRect.x + (popupRect.width - 150) / 2, popupRect.y + 320, 150, 50 };

    titlePos = { popupRect.x + popupRect.width / 2, popupRect.y + 60 };
    subtitlePos = { popupRect.x + popupRect.width / 2, popupRect.y + 120 };
    inputTextPos = { inputRect.x + 15, inputRect.y + 18 };
    font = LoadFont("assets/fonts/LilitaOne-Regular.ttf");

    show(1); 
}

NameInputPopUp::~NameInputPopUp(){
    UnloadFont(font);
}

// Updated show method to handle both new game and map completion
void NameInputPopUp::show(int mapNum){
    if (!isActive) {
        isActive = true;
        isAnimating = true;
        animationTimer = 0.0f;
        popupScale = 0.0f;
        playerName = "";
        mapNumber = mapNum;
        blinkTimer = 0;
        showCursor = true;
    }
}

void NameInputPopUp::hide(){
    isActive = false;
    isAnimating = false;
}

void NameInputPopUp::processInput(){}

void NameInputPopUp::update(float deltaTime){
    if (!isActive) return;

    if (isAnimating) {
        animationTimer += GetFrameTime();
        popupScale = std::min(1.0f, animationTimer * 3.0f); 

        popupScale = 1.0f - std::pow(1.0f - popupScale, 3.0f);

        if (popupScale >= 1.0f) {
            isAnimating = false;
        }
    }

    blinkTimer++;
    if (blinkTimer >= 30) { // Blink every 0.5 seconds at 60 FPS
        showCursor = !showCursor;
        blinkTimer = 0;
    }

    int key = GetCharPressed();
    while (key > 0) {
        if ((key >= 32) && (key <= 125) && playerName.length() < 20) {
            playerName += static_cast<char>(key);
        }
        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE) && !playerName.empty()) {
        playerName.pop_back();
    }

    bool enterPressed = IsKeyPressed(KEY_ENTER) && !playerName.empty();
    bool buttonClicked = false;

    if (CheckCollisionPointRec(GetMousePosition(), buttonRect)) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !playerName.empty()) {
            buttonClicked = true;
        }
    }

    if (enterPressed || buttonClicked) {
        hide();
        StateManager::getInstance().pushState(std::make_unique<SubMenu>());
    }
}

void NameInputPopUp::render(){
    if (!isActive) return;

    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), overlayColor);

    Vector2 center = { popupRect.x + popupRect.width / 2, popupRect.y + popupRect.height / 2 };

    Rectangle scaledPopup = {
        center.x - (popupRect.width * popupScale) / 2,
        center.y - (popupRect.height * popupScale) / 2,
        popupRect.width * popupScale,
        popupRect.height * popupScale
    };

    // Draw shadow
    DrawRectangleRounded({ scaledPopup.x + 5, scaledPopup.y + 5, scaledPopup.width, scaledPopup.height },
        0.05f, 20, { 0, 0, 0, 100 });

    DrawRectangleRounded(scaledPopup, 0.05f, 20, popupBg);
    DrawRectangleRoundedLines(scaledPopup, 0.05f, 20, 3, popupBorder);

    if (popupScale < 0.8f) return; // Don't draw text until popup is mostly visible

    std::string title, subtitle;
    
    if (true) {
        title = "A NEW HERO RISES!";
        subtitle = "Let history remember your name";
    } else {
        title = "MAP " + std::to_string(mapNumber) + " COMPLETED!";
        subtitle = "Victory is yours, champion!";
    }

    Vector2 titleSize = MeasureTextEx(font, title.c_str(), 36, 2);

    for (int i = 0; i < 1; i++) {
        DrawTextEx(font, title.c_str(),
            { titlePos.x - titleSize.x / 2 + i, titlePos.y - titleSize.y / 2 + i },
            36, 2, { 255, 215, 0, 80 });
    }
    DrawTextEx(font, title.c_str(),
        { titlePos.x - titleSize.x / 2, titlePos.y - titleSize.y / 2 },
        36, 2, titleColor);

    Vector2 subtitleSize = MeasureTextEx(font, subtitle.c_str(), 25, 1);
    DrawTextEx(font, subtitle.c_str(),
        { subtitlePos.x - subtitleSize.x / 2, subtitlePos.y - subtitleSize.y / 2 },
        25, 1, textColor);

    Rectangle scaledInput = {
        inputRect.x * popupScale + center.x * (1 - popupScale),
        inputRect.y * popupScale + center.y * (1 - popupScale),
        inputRect.width * popupScale,
        inputRect.height * popupScale
    };

    DrawRectangleRounded(scaledInput, 0.1f, 10, inputBg);
    DrawRectangleRoundedLines(scaledInput, 0.1f, 10, 2, inputBorder);

    std::string displayText = playerName;
    if (showCursor && playerName.length() < 20) {
        displayText += "|";
    }

    Vector2 scaledInputTextPos = {
        inputTextPos.x * popupScale + center.x * (1 - popupScale),
        inputTextPos.y * popupScale + center.y * (1 - popupScale)
    };

    DrawTextEx(font, displayText.c_str(), scaledInputTextPos, 24, 1, textColor);

    if (playerName.empty() && !showCursor) {
        DrawTextEx(font, "What shall we call you, Player?",
            scaledInputTextPos, 24, 1, { 150, 150, 150, 255 });
    }

    Rectangle scaledButton = {
        buttonRect.x * popupScale + center.x * (1 - popupScale),
        buttonRect.y * popupScale + center.y * (1 - popupScale),
        buttonRect.width * popupScale,
        buttonRect.height * popupScale
    };

    Color currentButtonColor = buttonColor;
    if (CheckCollisionPointRec(GetMousePosition(), scaledButton) && !playerName.empty()) {
        currentButtonColor = buttonHover;
    }
    if (playerName.empty()) {
        currentButtonColor = { 100, 100, 100, 255 };
    }

    DrawRectangleRounded(scaledButton, 0.2f, 10, currentButtonColor);

    std::string buttonText = "Let's go !";
    Vector2 buttonTextSize = MeasureTextEx(font, buttonText.c_str(), 22, 1);
    Vector2 buttonTextPos = {
        scaledButton.x + (scaledButton.width - buttonTextSize.x) / 2,
        scaledButton.y + (scaledButton.height - buttonTextSize.y) / 2
    };
    DrawTextEx(font, buttonText.c_str(), buttonTextPos, 22, 1, WHITE);

    // std::string instruction = "Press ENTER or click BEGIN QUEST";
    // Vector2 instrSize = MeasureTextEx(font, instruction.c_str(), 16, 1);
    // DrawTextEx(font, instruction.c_str(),
    //     { center.x - instrSize.x / 2, scaledButton.y + scaledButton.height + 20 },
    //     16, 1, { 200, 200, 200, 255 });
}