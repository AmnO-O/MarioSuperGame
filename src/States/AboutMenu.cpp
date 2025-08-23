#include "States/AboutMenu.h"
#include "States/MainMenu.h"

AboutMenu::AboutMenu() : 
    return_button("assets/images/turn_back_white.png", {25, 27, 100, 100}, [&]() {
        StateManager::getInstance().pushState(std::make_unique<MainMenu>());
    })
{
    font = LoadFont("assets/fonts/LilitaOne-Regular.ttf");
    background = LoadTexture("assets/images/sub_menu_background.png");
    return_button_state = LoadTexture("assets/images/turn_back_red.png");
}

AboutMenu::~AboutMenu()
{
    UnloadTexture(background);
    UnloadTexture(return_button_state);
    UnloadFont(font);
}

void AboutMenu::update(float deltaTime)
{
    return_button.update(deltaTime);
}

void AboutMenu::render()
{
    DrawTexture(background, 0, 0, WHITE);

    DrawTextEx(font, info1.c_str(), {240, 50}, 50, 2, BLACK);
    DrawTextEx(font, info2.c_str(), {200, 100}, 50, 2, BLACK);
    DrawTextEx(font, info3.c_str(), {200, 150}, 50, 2, BLACK);
    DrawTextEx(font, info4.c_str(), {200, 200}, 50, 2, BLACK);
    DrawTextEx(font, info5.c_str(), {200, 250}, 50, 2, BLACK);
    DrawTextEx(font, info6.c_str(), {200, 300}, 50, 2, BLACK);

    DrawTextEx(font, con.c_str(), {240, 370}, 50, 2, BLACK);
    DrawTextEx(font, Nam.c_str(), {550, 370}, 50, 2, BLACK);
    DrawTextEx(font, Phong.c_str(), {550, 420}, 50, 2, BLACK);
    DrawTextEx(font, Vi.c_str(), {550, 470}, 50, 2, BLACK);
    DrawTextEx(font, Vinh.c_str(), {550, 520}, 50, 2, BLACK);

    return_button.render();
    bool isHovered = CheckCollisionPointRec(GetMousePosition(), return_button.getBounds());
    if (isHovered)  
        DrawTexture(return_button_state, 25, 27, WHITE);
}

