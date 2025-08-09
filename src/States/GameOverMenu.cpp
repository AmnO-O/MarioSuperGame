#include "States/GameOverMenu.h"
#include "States/MainMenu.h"
#include "States/World.h"

GameOverMenu::GameOverMenu()
  : title("GAME OVER"),
    restart_button("RESTART", {641, 509, 330, 50}, WHITE, RED, [&]() {
        StatsManager::getInstance().reset();
        StateManager::getInstance().popState();
        bool isMario = dynamic_cast<World*>(StateManager::getInstance().getCurrentState())->getIsMario();
        int mapIndex = dynamic_cast<World*>(StateManager::getInstance().getCurrentState())->getMapIndex();
        StateManager::getInstance().pushState(std::make_unique<World>(isMario, mapIndex));

        StopSound(SoundManager::getInstance().gameOverSound);
        PlayMusicStream(SoundManager::getInstance().playMusic);
        SoundManager::getInstance().death_played = false;
        SoundManager::getInstance().game_over_played = false;
    }),
    exit_button("EXIT", {707, 620, 330, 50}, WHITE, RED, [&]() {
        StatsManager::getInstance().reset();
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
