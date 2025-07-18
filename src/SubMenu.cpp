#include "SubMenu.h"
#include "MainMenu.h"

SubMenu::SubMenu(StateManager& stateManager, const std::string& title)
  : stateManager(stateManager),
    new_game_button("NEW GAME", {656, 294, 330, 60}, WHITE, RED, []() {}),
    load_game_button("LOAD GAME", {644, 399, 330, 60}, WHITE, RED, []() {}),
    return_button("D:/MarioSuperGame/assets/images/return_button.png", {25, 27, 100, 100}, [&]() {
        stateManager.pushState(std::make_unique<MainMenu>(stateManager));
    }),
    title(title) 
{
    sub_background = LoadTexture("D:/MarioSuperGame/assets/images/sub_menu_background.png");
}

void SubMenu::unload() {
    UnloadTexture(sub_background);
}

void SubMenu::update(float deltaTime) {
    new_game_button.update(deltaTime);
    load_game_button.update(deltaTime);
    return_button.update(deltaTime);
}

void SubMenu::render() {
    DrawTexture(sub_background, 0, 0, WHITE);

    new_game_button.render();
    load_game_button.render();
    return_button.render();

    DrawText(title.c_str(), 577, 79, 50, BLACK);
}