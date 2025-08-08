#include "States/SubMenu.h"
#include "States/MainMenu.h"
#include "States/LevelMenu.h"

SubMenu::SubMenu(bool checkMario)
  : isMario(checkMario),
    new_game_button("NEW GAME", {625, 294, 330, 60}, WHITE, RED, [&]() {
        StateManager::getInstance().pushState(std::make_unique<LevelMenu>(isMario));
    }),
    load_game_button("LOAD GAME", {598, 399, 330, 60}, WHITE, RED, []() {}),
    return_button("assets/images/turn_back.png", {25, 27, 100, 100}, [&]() {
        StateManager::getInstance().pushState(std::make_unique<MainMenu>());
    }) 
{
    if (isMario)
        title = "MARIO GAME";
    else
        title = "LUIGI GAME";
    
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
    new_game_button.update(deltaTime);
    load_game_button.update(deltaTime);
    return_button.update(deltaTime);
}

void SubMenu::render() 
{
    DrawTexture(sub_background, 0, 0, WHITE);

    new_game_button.render();
    load_game_button.render();
    return_button.render();

    bool isHovered = CheckCollisionPointRec(GetMousePosition(), return_button.getBounds());
    if (isHovered)
        DrawTexture(return_button_state, 25, 27, WHITE);

    DrawTextEx(titleFont, title.c_str(), {577, 79}, 50, 2, BLACK);
}