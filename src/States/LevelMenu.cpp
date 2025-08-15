#include "States/LevelMenu.h"
#include "States/SubMenu.h"
#include "States/World.h"
#include "Resources/Timer.h"
#include "Resources/StatsManager.h"

LevelMenu::LevelMenu(bool checkMario)
  : isMario(checkMario),
    title("CHOOSE YOUR LEVEL"), 
    high_score(loadHighScore()),
    return_button("assets/images/turn_back_white.png", {25,27,100,100}, [&]() {
        StateManager::getInstance().pushState(std::make_unique<SubMenu>());
        StatsManager::getInstance().reset();
    }),
    world1_1("assets/images/World1-1.png", {73, 277, 532, 208}, [&]() {
        StateManager::getInstance().pushState(std::make_unique<World>(isMario, 1, 300.0f));
        StatsManager::getInstance().reset();
    }),
    world1_2("assets/images/World1-2.png", {977, 277, 532, 208}, [&]() {
        StateManager::getInstance().pushState(std::make_unique<World>(isMario, 2, 300.0f));
        StatsManager::getInstance().reset();
    }),
    world1_3("assets/images/World1-3.png", {73, 635, 532, 208}, []() {}),
    world1_4("assets/images/World1-4.png", {977, 635, 532, 208}, []() {})
{
    level_background = LoadTexture("assets/images/blue_background.png");
    return_button_state = LoadTexture("assets/images/turn_back_red.png");
    font = LoadFont("assets/fonts/SuperMarioBros.ttf");
}

LevelMenu::~LevelMenu()
{
    UnloadFont(font);
    UnloadTexture(level_background);
    UnloadTexture(return_button_state);
}

std::string LevelMenu::loadHighScore()
{
    int highScore = StatsManager::getInstance().getHighScore();
    int maxDigits = 6;

    std::string highScoreStr = std::to_string(highScore);
    if (highScoreStr.length() < maxDigits) 
    {
        int remaining = maxDigits - (int)highScoreStr.length();
        highScoreStr.insert(0, remaining, '0');
    }

    return "TOP-" + highScoreStr;
}

void LevelMenu::drawBorder(Rectangle bounds)
{
    bool isHovered = CheckCollisionPointRec(GetMousePosition(), bounds);
    Color border_color = isHovered ? RED : BLACK;
    DrawRectangleLinesEx(bounds, 5, border_color);
}

void LevelMenu::update(float deltaTime) 
{

    world1_1.update(deltaTime);
    world1_2.update(deltaTime);
    world1_3.update(deltaTime);
    world1_4.update(deltaTime);

    return_button.update(deltaTime);
}

void LevelMenu::render() 
{
    
    DrawTexture(level_background, 0, 0, WHITE);

    drawBorder(world1_1.getBounds());
    drawBorder(world1_2.getBounds());
    drawBorder(world1_3.getBounds());
    drawBorder(world1_4.getBounds());

    world1_1.render();
    world1_2.render();
    world1_3.render();
    world1_4.render();

    return_button.render();
    bool buttonHovered = CheckCollisionPointRec(GetMousePosition(), return_button.getBounds());
    if (buttonHovered)
        DrawTexture(return_button_state, 25, 27, WHITE);

    DrawTextEx(font, title.c_str(), {410, 104}, 50, 2, BLACK);
    DrawTextEx(font, high_score.c_str(), {1088, 20}, 50, 2, BLACK);
}

