#include "SettingsMenu.h"
#include "MainMenu.h"
#include "LevelMenu.h"
#include "SoundManager.h"

SettingsMenu::SettingsMenu(StateManager& stateManager, SoundManager& soundManager)
  : stateManager(stateManager),
    soundManager(soundManager),
    slider(600, 600, 300, 20, soundManager),
    return_button("D:/MarioSuperGame/assets/images/turn_back.png", {25, 27, 100, 100}, [&]() {
        stateManager.popState();
        stateManager.pushState(std::make_unique<MainMenu>(stateManager, soundManager));
    }),
    music_button("ON", {600, 450, 330, 60}, WHITE, RED, []() {}),
    soundFX_button("ON", {600, 533, 330, 60}, WHITE, RED, []() {}),
    music("MUSIC"),
    soundFX("SOUND FX") 
{    
    settings_background = LoadTexture("D:/MarioSuperGame/assets/images/sub_menu_background_2.png");
    font = LoadFont("D:/MarioSuperGame/assets/fonts/SuperMarioBros.ttf");
}

SettingsMenu::~SettingsMenu()
{
    UnloadFont(font);
    UnloadTexture(settings_background);
}

void SettingsMenu::update(float deltaTime) 
{
    music_button.update(deltaTime);
    soundFX_button.update(deltaTime);
    return_button.update(deltaTime);

    slider.update();
}

void SettingsMenu::render() 
{
    DrawTexture(settings_background, 0, 0, WHITE);

    music_button.render();
    soundFX_button.render();
    return_button.render();
    slider.render(font);

    DrawTextEx(font, music.c_str(), {200, 400}, 50, 2, BLACK);
    DrawTextEx(font, soundFX.c_str(), {200, 500}, 50, 2, BLACK);
}