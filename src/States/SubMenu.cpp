#include "States/SubMenu.h"
#include "States/MainMenu.h"
#include "States/LevelMenu.h"
#include "States/World.h"

SubMenu::SubMenu()
  : mario_button("MARIO GAME", {(GetScreenWidth() * 1.f - 350.0f) / 2.0f, 400, 350, 60}, WHITE, RED, [&]() { 
        StateManager::getInstance().pushState(std::make_unique<LevelMenu>(true));  
    }),
    luigi_button("LUIGI GAME", {(GetScreenWidth() * 1.f - 350.0f) / 2.0f, 533, 350, 60}, WHITE, RED, [&]() { 
        StateManager::getInstance().pushState(std::make_unique<LevelMenu>(false));
    }), 
    return_button("assets/images/turn_back_white.png", {25, 27, 100, 100}, [&]() {
        StateManager::getInstance().pushState(std::make_unique<MainMenu>());
    }),
    title("CHOOSE YOUR CHARACTER") 
{
    sub_background = LoadTexture("assets/images/sub_menu_background.png");
    return_button_state = LoadTexture("assets/images/turn_back_red.png");
    titleFont = LoadFont("assets/fonts/SuperMarioBros.ttf");
}

SubMenu::~SubMenu()
{
    UnloadFont(titleFont);
    UnloadTexture(sub_background);
    UnloadTexture(return_button_state);
}

void SubMenu::update(float deltaTime) 
{
    mario_button.update(deltaTime);
    luigi_button.update(deltaTime);
    return_button.update(deltaTime);
}

void SubMenu::render() 
{
    DrawTexture(sub_background, 0, 0, WHITE);

    mario_button.render();
    luigi_button.render();
    return_button.render();

    bool isHovered = CheckCollisionPointRec(GetMousePosition(), return_button.getBounds());
    if (isHovered)
        DrawTexture(return_button_state, 25, 27, WHITE);

    DrawTextEx(titleFont, title.c_str(), {324, 79}, 50, 2, BLACK);
}