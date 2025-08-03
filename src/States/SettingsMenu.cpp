#include "States/SettingsMenu.h"
#include "States/MainMenu.h"
#include "States/LevelMenu.h"
#include "Resources/SoundManager.h"

SettingsMenu::SettingsMenu(StateManager& stateManager, SoundManager& soundManager)
  : stateManager(stateManager),
    soundManager(soundManager),
    slider({686, 245, 449, 35}, soundManager),
    return_button("assets/images/turn_back.png", {25, 27, 100, 100}, [&]() {
        //stateManager.popState();
        stateManager.pushState(std::make_unique<MainMenu>(stateManager, soundManager));
    }),
    music("MUSIC:"),
    soundFX("SOUND FX:") 
{    
    settings_background = LoadTexture("assets/images/blue_background.png");
    return_button_state = LoadTexture("assets/images/turn_back_red.png");
    font = LoadFont("assets/fonts/SuperMarioBros.ttf");
}

SettingsMenu::~SettingsMenu()
{
    UnloadFont(font);
    UnloadTexture(settings_background);
    UnloadTexture(return_button_state);
}

void SettingsMenu::update(float deltaTime) 
{
    return_button.update(deltaTime);
    slider.update();
}

void SettingsMenu::render() 
{
    DrawTexture(settings_background, 0, 0, WHITE);
    
    return_button.render();
    slider.render();

    bool isHovered = CheckCollisionPointRec(GetMousePosition(), return_button.getBounds());
    if (isHovered)  
        DrawTexture(return_button_state, 25, 27, WHITE);

    DrawTextEx(font, music.c_str(), {258, 239}, 50, 2, BLACK);
    DrawTextEx(font, soundFX.c_str(), {258, 353}, 50, 2, BLACK);
}