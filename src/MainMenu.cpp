#include "MainMenu.h"
#include "SubMenu.h"

MainMenu::MainMenu(std::function<void(std::unique_ptr<MenuState>)> switchStateCallback)
: mario_button("MARIO GAME", {615, 450, 330, 60}, WHITE, RED, [switchStateCallback]() { 
    switchStateCallback(std::make_unique<SubMenu>(switchStateCallback, "MARIO SELECTED"));  
    }),
      luigi_button("LUIGI GAME", {615, 533, 330, 60}, WHITE, RED, [switchStateCallback]() { 
    switchStateCallback(std::make_unique<SubMenu>(switchStateCallback, "LUIGI SELECTED"));
    })
{
    background = LoadTexture("D:/MarioSuperGame/assets/images/main_menu_background.png"); 
}

void MainMenu::unload() 
{
    UnloadTexture(background);
}

void MainMenu::update(float deltaTime) 
{
    mario_button.update(deltaTime);
    luigi_button.update(deltaTime);
}

void MainMenu::render() 
{
    DrawTexture(background, 0, 0, WHITE);

    mario_button.render(); 
    luigi_button.render(); 
}