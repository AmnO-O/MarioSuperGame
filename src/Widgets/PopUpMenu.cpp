#include "Widgets/PopUpMenu.h"
#include "Resources/SoundManager.h"
#include "Resources/StateManager.h"
#include "States/MainMenu.h"
#include "States/World.h"

PopUpMenu::PopUpMenu()
  : isVisible(false),
    resume_button("RESUME", {663, 296, 330, 50}, WHITE, RED, [&](){
        toggle();
    }),
    restart_button("RESTART", {639, 392, 330, 50}, WHITE, RED, [&]() {
        restart();
    }),
    exit_button("EXIT", {710, 488, 330, 50}, WHITE, RED, [&]() {
        exitGame();
    }),
    save_button("SAVE GAME", {594, 584, 330, 50}, WHITE, RED, []() {

    }),
    frame({500, 225, 600, 472})
{

}

void PopUpMenu::restart()
{
    bool isMario = dynamic_cast<World*>(StateManager::getInstance().getCurrentState())->getIsMario();
    int mapIndex = dynamic_cast<World*>(StateManager::getInstance().getCurrentState())->getMapIndex();
    StatsManager::getInstance().reset();
    StateManager::getInstance().pushState(std::make_unique<World>(isMario, mapIndex));
    ResumeMusicStream(SoundManager::getInstance().playMusic);
}

void PopUpMenu::exitGame()
{
    StatsManager::getInstance().reset();
    StateManager::getInstance().pushState(std::make_unique<MainMenu>());
    ResumeMusicStream(SoundManager::getInstance().playMusic);
}

void PopUpMenu::toggle()
{
    isVisible = !isVisible;

    if (isVisible)
        PauseMusicStream(SoundManager::getInstance().playMusic);
    else
        ResumeMusicStream(SoundManager::getInstance().playMusic);
}

void PopUpMenu::update(float deltaTime)
{
    if (isVisible)
    {
        resume_button.update(deltaTime);
        restart_button.update(deltaTime);
        exit_button.update(deltaTime);
        save_button.update(deltaTime);
    }
}

void PopUpMenu::render()
{
    if (isVisible)
    {
        DrawRectangleRec(frame, Fade(BLACK, 0.8f));
        DrawRectangleLinesEx(frame, 5, WHITE);

        resume_button.render();
        restart_button.render();
        exit_button.render();
        save_button.render();
    }
}