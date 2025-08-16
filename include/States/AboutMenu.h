#pragma once
#include "../Resources/StateManager.h"
#include "raylib.h"
#include "../Widgets/Button.h"

class AboutMenu : public GameState
{
private:
    Font font;
    Texture2D background;
    NormalButton back_button;
public:
    AboutMenu() = default;
    ~AboutMenu(){
        UnloadFont(font);
        UnloadTexture(background);
    }

    void processInput() override{}
    void update(float deltaTime) override{}
    void render() override{}

    void backToMainMenu();
};