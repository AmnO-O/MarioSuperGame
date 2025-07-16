#include "MainMenu.h"

MainMenu::MainMenu()
: one_player_button("MARIO GAME", {347, 596, 330, 60}, WHITE, RED, []() { /* Open one-player submenu */ }),
      two_player_button("LUIGI GAME", {347, 670, 330, 60}, WHITE, RED, []() { /* Open two-player submenu */ }),
      settings_button() // Placeholder for ImageButton initialization
{
    background = LoadTexture("D:/MarioSuperGame/assets/background.png"); 
}

void MainMenu::unload() 
{
    UnloadTexture(background);
}

void MainMenu::update(float deltaTime) 
{
    one_player_button.update(deltaTime);
    two_player_button.update(deltaTime);
}

void MainMenu::render() 
{
    DrawTexture(background, 0, 0, WHITE);

    one_player_button.render(); 
    two_player_button.render(); 
}