#include "MainMenu.h"
#include "SubMenu.h"
#include "SettingsMenu.h"

MainMenu::MainMenu(StateManager& stateManager, SoundManager& soundManager)
  : stateManager(stateManager), 
    soundManager(soundManager),   
    mario_button("MARIO GAME", {615, 450, 330, 60}, WHITE, RED, [&]() { 
        stateManager.popState();
        stateManager.pushState(std::make_unique<SubMenu>(stateManager, soundManager, true));  
    }),
    luigi_button("LUIGI GAME", {615, 533, 330, 60}, WHITE, RED, [&]() { 
        stateManager.popState();
        stateManager.pushState(std::make_unique<SubMenu>(stateManager, soundManager, false));
    }), 
    settings_button("D:/MarioSuperGame/assets/images/setting.png", {25, 27, 100, 100}, [&]() {
        stateManager.popState();       
        stateManager.pushState(std::make_unique<SettingsMenu>(stateManager, soundManager));
    })
{
    background = LoadTexture("D:/MarioSuperGame/assets/images/main_menu_background.png"); 
}

MainMenu::~MainMenu() 
{
    UnloadTexture(background);
}

void MainMenu::update(float deltaTime) 
{
    mario_button.update(deltaTime);
    luigi_button.update(deltaTime);
    settings_button.update(deltaTime);
}

void MainMenu::render() 
{
    DrawTexture(background, 0, 0, WHITE);

    mario_button.render(); 
    luigi_button.render(); 
    settings_button.render();
}