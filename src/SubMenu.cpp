#include "SubMenu.h"
#include "MainMenu.h"
#include "LevelMenu.h"

SubMenu::SubMenu(StateManager& stateManager, SoundManager& soundManager, bool checkMario)
  : stateManager(stateManager),
    soundManager(soundManager),
    isMario(checkMario),
    new_game_button("NEW GAME", {625, 294, 330, 60}, WHITE, RED, [&]() {
        //stateManager.popState();
        stateManager.pushState(std::make_unique<LevelMenu>(stateManager, soundManager, isMario));
    }),
    load_game_button("LOAD GAME", {598, 399, 330, 60}, WHITE, RED, []() {}),
    return_button("D:/MarioSuperGame/assets/images/turn_back.png", {25, 27, 100, 100}, [&]() {
        //stateManager.popState();
        stateManager.pushState(std::make_unique<MainMenu>(stateManager, soundManager));
    }) 
{
    if (isMario)
        title = "MARIO GAME";
    else
        title = "LUIGI GAME";
    
    sub_background = LoadTexture("D:/MarioSuperGame/assets/images/sub_menu_background.png");
    titleFont = LoadFont("D:/MarioSuperGame/assets/fonts/SuperMarioBros.ttf");
}

SubMenu::~SubMenu()
{
    UnloadFont(titleFont);
    UnloadTexture(sub_background);
}

void SubMenu::update(float deltaTime) 
{
    new_game_button.update(deltaTime);
    load_game_button.update(deltaTime);
    return_button.update(deltaTime);
}

void SubMenu::render() 
{
    DrawTexture(sub_background, 0, 0, WHITE);

    new_game_button.render();
    load_game_button.render();
    return_button.render();

    DrawTextEx(titleFont, title.c_str(), {577, 79}, 50, 2, BLACK);
}