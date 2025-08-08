#include "States/GameOverMenu.h"
#include "States/MainMenu.h"
#include "States/World11.h"

GameOverMenu::GameOverMenu()
  : title("GAME OVER"),
    restart_button("RESTART", {641, 509, 330, 50}, WHITE, RED, [&]() {
        StateManager::getInstance().popState();
        bool isMario = dynamic_cast<World1_1*>(StateManager::getInstance().getCurrentState())->getIsMario();
        StateManager::getInstance().pushState(std::make_unique<World1_1>(isMario)); // needs changing
        StopSound(SoundManager::getInstance().deathSound);
        PlayMusicStream(SoundManager::getInstance().playMusic);
        SoundManager::getInstance().death_played = false;
        SoundManager::getInstance().game_over_played = false;
    }),
    exit_button("EXIT", {707, 620, 330, 50}, WHITE, RED, [&]() {
        StateManager::getInstance().pushState(std::make_unique<MainMenu>());
        StopSound(SoundManager::getInstance().gameOverSound);
        PlayMusicStream(SoundManager::getInstance().playMusic);
        SoundManager::getInstance().death_played = false;
        SoundManager::getInstance().game_over_played = false;
    })
{
    font = LoadFont("assets/fonts/SuperMarioBros.ttf");
}

void GameOverMenu::update(float deltaTime)
{
    restart_button.update(deltaTime);
    exit_button.update(deltaTime);
}

void GameOverMenu::render()
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), { 0, 0, 0, 255 });
    DrawTextEx(font, title.c_str(), {598, 311}, 50, 2, WHITE);
    
    restart_button.render();
    exit_button.render();
}
