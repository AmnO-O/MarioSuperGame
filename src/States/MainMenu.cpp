#include "States/MainMenu.h"
#include "States/SubMenu.h"
#include "States/SettingsMenu.h"

MainMenu::MainMenu(StateManager& stateManager, SoundManager& soundManager)
  : stateManager(stateManager), 
    soundManager(soundManager),   
    mario_button("MARIO GAME", {570, 450, 330, 60}, WHITE, RED, [&]() { 
        //stateManager.popState();
        stateManager.pushState(std::make_unique<SubMenu>(stateManager, soundManager, true));  
    }),
    luigi_button("LUIGI GAME", {570, 533, 330, 60}, WHITE, RED, [&]() { 
        //stateManager.popState();
        stateManager.pushState(std::make_unique<SubMenu>(stateManager, soundManager, false));
    }), 
    settings_button("assets/images/setting.png", {25, 27, 100, 100}, [&]() {
        //stateManager.popState();       
        stateManager.pushState(std::make_unique<SettingsMenu>(stateManager, soundManager));
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

    bool isHovered = CheckCollisionPointRec(GetMousePosition(), settings_button.getBounds());
    if (isHovered)
        DrawTexture(settings_button_state, 25, 27, WHITE);
}