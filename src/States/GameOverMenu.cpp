#include "States/GameOverMenu.h"
#include "States/MainMenu.h"
#include "States/World.h"
#include "Resources/StatsManager.h"


GameOverMenu::GameOverMenu(int mapIndex, bool checkMario)
  : title("GAME OVER"),
    prevMapIndex(mapIndex),
    isprevMario(checkMario),
    restart_button("RESTART", {641, 509, 330, 50}, WHITE, RED, [&]() {
        restart();
    }),
    exit_button("EXIT", {707, 620, 330, 50}, WHITE, RED, [&]() {
        exitGame();
    })
{
    font = LoadFont("assets/fonts/SuperMarioBros.ttf");
}

void GameOverMenu::drawStats()
{
    std::string score = "SCORE";
    DrawTextEx(font, score.c_str(), {203, 33}, 40, 2, WHITE);

    int score_number = StatsManager::getInstance().getScore();
    int number_of_coins = StatsManager::getInstance().getCoins();

    int maxDigit = 6;
    int scoreDigits = (int)std::to_string(score_number).length();
    std::string scoreStr;

    if (scoreDigits <= maxDigit)
    {
        int remaining = maxDigit - scoreDigits;
        for (int i=0; i<remaining; i++)
            scoreStr += "0";

        scoreStr += std::to_string(score_number);
    }

    DrawTextEx(font, scoreStr.c_str(), {203, 86}, 40, 2, WHITE);

    std::string coins = "COINS";
    DrawTextEx(font, coins.c_str(), {572, 33}, 40, 2, WHITE);

    int maxCoinsDigits = 2;
    int coinsDigits = (int)std::to_string(number_of_coins).length();
    std::string coinsStr;

    if (coinsDigits <= maxCoinsDigits)
    {
        int remaining = maxCoinsDigits - coinsDigits;
        for (int i=0; i<remaining; i++)
            coinsStr += "0";

        coinsStr += std::to_string(number_of_coins);
    }

    DrawTextEx(font, coinsStr.c_str(), {630, 86}, 40, 2, WHITE);

    std::string w = "WORLD"; std::string title;
    DrawTextEx(font, w.c_str(), {941, 33}, 40, 2, WHITE);

    if (prevMapIndex == 1)
        title = "1-1";
    else if (prevMapIndex == 2)
        title = "1-2";
    else if (prevMapIndex == 3)
        title = "1-3";
    else if (prevMapIndex == 4)
        title = "1-4";
    
    DrawTextEx(font, title.c_str(), {984, 86}, 40, 2, WHITE);

    std::string time = "TIME";
    DrawTextEx(font, time.c_str(), {1308, 33}, 40, 2, WHITE);   
    int totalSec = (int)floorf(Timer::getInstance().remaining + 0.0001f); // small epsilon for safety
    int mins = totalSec / 60;
    int secs = totalSec % 60;

    std::string timeDisplay = (mins < 10 ? "0" : "") + std::to_string(mins) + ":" + (secs < 10 ? "0" : "") + std::to_string(secs);
    DrawTextEx(font, timeDisplay.c_str(), {1300, 86}, 40, 2, WHITE);
}

void GameOverMenu::restart()
{
    StatsManager::getInstance().reset();
    // StateManager::getInstance().popState();
    
    StateManager::getInstance().pushState(std::make_unique<World>(isprevMario, prevMapIndex, 60.0f));
    StopSound(SoundManager::getInstance().gameOverSound);
    PlayMusicStream(SoundManager::getInstance().playMusic);
    SoundManager::getInstance().death_played = false;
    SoundManager::getInstance().game_over_played = false;
}

void GameOverMenu::exitGame()
{
    StatsManager::getInstance().reset();
    StateManager::getInstance().pushState(std::make_unique<MainMenu>());
    StopSound(SoundManager::getInstance().gameOverSound);
    PlayMusicStream(SoundManager::getInstance().playMusic);
    SoundManager::getInstance().death_played = false;
    SoundManager::getInstance().game_over_played = false;
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

    drawStats();
}


