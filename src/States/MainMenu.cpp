#include "States/MainMenu.h"
#include "States/SubMenu.h"
#include "States/SettingsMenu.h"
#include "tinyfiledialogs.h"
#include "States/World.h"

MainMenu::MainMenu()  
  : new_game_button("NEW GAME", {570, 450, 330, 60}, WHITE, RED, [&]() {
        StateManager::getInstance().pushState(std::make_unique<SubMenu>());
    }),
    load_game_button("LOAD GAME", {570, 533, 330, 60}, WHITE, RED, [&]() {
        const char* filename = tinyfd_openFileDialog(
        "Load Game", "", 1, (const char*[]){"*.txt"}, "Text Files", 0);
    }),
    settings_button("assets/images/setting.png", {25, 27, 100, 100}, [&]() {
        StateManager::getInstance().pushState(std::make_unique<SettingsMenu>());
    })
{
    background = LoadTexture("assets/images/main_menu_background.png"); 
    settings_button_state = LoadTexture("assets/images/setting_red.png");
}



MainMenu::~MainMenu() 
{
    UnloadTexture(background);
    UnloadTexture(settings_button_state);
}

void MainMenu::update(float deltaTime) 
{
    new_game_button.update(deltaTime);
    load_game_button.update(deltaTime);
    settings_button.update(deltaTime);
}

void MainMenu::render() 
{
    DrawTexture(background, 0, 0, WHITE);

    new_game_button.render(); 
    load_game_button.render(); 
    settings_button.render();

    bool isHovered = CheckCollisionPointRec(GetMousePosition(), settings_button.getBounds());
    if (isHovered)
        DrawTexture(settings_button_state, 25, 27, WHITE);
}