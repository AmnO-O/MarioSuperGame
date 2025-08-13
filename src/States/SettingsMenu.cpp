#include "States/SettingsMenu.h"
#include "States/MainMenu.h"
#include "States/LevelMenu.h"
#include "Resources/SoundManager.h"

SettingsMenu::SettingsMenu()
  : music_slider({686, 245, 449, 35}, false),
    effect_slider({686, 359, 449, 35}, true),
    return_button("assets/images/turn_back_white.png", {25, 27, 100, 100}, [&]() {
        StateManager::getInstance().pushState(std::make_unique<MainMenu>());
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
    music_slider.update();
    effect_slider.update();
}

void SettingsMenu::render() 
{
    DrawTexture(settings_background, 0, 0, WHITE);
    
    return_button.render();
    music_slider.render();
    effect_slider.render();

    bool isHovered = CheckCollisionPointRec(GetMousePosition(), return_button.getBounds());
    if (isHovered)  
        DrawTexture(return_button_state, 25, 27, WHITE);

    DrawTextEx(font, music.c_str(), {258, 239}, 50, 2, BLACK);
    DrawTextEx(font, soundFX.c_str(), {258, 353}, 50, 2, BLACK);
}