#include "States/EndResult.h"
#include "States/MainMenu.h"
#include "States/World.h"
#include "Resources/Timer.h"
#include <fstream>

EndResult::EndResult(int mIndex, bool checkMario)
    : title("LEVEL COMPLETED!"),
      continue_button("CONTINUE", { (GetScreenWidth() * 1.0f - 330.f) / 2.0f, 580, 330, 50}, WHITE, RED, [&]() {
        toNextLevel(); 
      }),
      prevMapIndex(mIndex),
      isMario(checkMario)
{
    font = LoadFont("assets/fonts/SuperMarioBros.ttf");

    if (prevMapIndex != 4)
        back_button.setUp("EXIT", { (GetScreenWidth() * 1.0f - 330.0f) / 2.0f, 691, 330, 50 }, WHITE, RED, [&]() {backToMainMenu();});
    else
        back_button.setUp("EXIT", { (GetScreenWidth() * 1.0f - 330.0f) / 2.0f, 580, 330, 50 }, WHITE, RED, [&]() {backToMainMenu();});
}

void EndResult::drawStats()
{
    std::string score = "SCORE:";
    DrawTextEx(font, score.c_str(), {511, 182}, 40, 2, WHITE);

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

    DrawTextEx(font, scoreStr.c_str(), {868, 182}, 40, 2, WHITE);

    std::string coins = "COINS:";
    DrawTextEx(font, coins.c_str(), {511, 276}, 40, 2, WHITE);

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

    DrawTextEx(font, coinsStr.c_str(), {1015, 276}, 40, 2, WHITE);

    std::string w = "WORLD:"; std::string title;
    DrawTextEx(font, w.c_str(), {511, 375}, 40, 2, WHITE);

    if (prevMapIndex == 1)
        title = "1-1";
    else if (prevMapIndex == 2)
        title = "1-2";
    else if (prevMapIndex == 3)
        title = "1-3";
    else if (prevMapIndex == 4)
        title = "1-4";
    
    DrawTextEx(font, title.c_str(), {985, 375}, 40, 2, WHITE);

    std::string time = "TIME:";
    DrawTextEx(font, time.c_str(), {511, 471}, 40, 2, WHITE);   
    int totalSec = (int)StatsManager::getInstance().time_taken; // small epsilon for safety
    int mins = totalSec / 60;
    int secs = totalSec % 60;

    std::string timeDisplay = (mins < 10 ? "0" : "") + std::to_string(mins) + ":" + (secs < 10 ? "0" : "") + std::to_string(secs);
    DrawTextEx(font, timeDisplay.c_str(), {904, 471}, 40, 2, WHITE);
}

void EndResult::backToMainMenu()
{
    StatsManager::getInstance().reset();
    StateManager::getInstance().pushState(std::make_unique<MainMenu>());
    StopSound(SoundManager::getInstance().endSound);
    PlayMusicStream(SoundManager::getInstance().playMusic);
    SoundManager::getInstance().death_played = false;
    SoundManager::getInstance().game_over_played = false;
}

void EndResult::toNextLevel()
{
    StatsManager::getInstance().reset(); 
    StopSound(SoundManager::getInstance().endSound);
    PlayMusicStream(SoundManager::getInstance().playMusic);
    SoundManager::getInstance().death_played = false;
    SoundManager::getInstance().game_over_played = false;
    if (prevMapIndex != 4)
        StateManager::getInstance().pushState(std::make_unique<World>(isMario, prevMapIndex + 1, 300.0f));
}

void EndResult::update(float deltaTime)
{
    back_button.update(deltaTime);
    if (prevMapIndex != 4)
        continue_button.update(deltaTime);
}

void EndResult::render()
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), { 0, 0, 0, 255 });
    
    DrawTextEx(font, title.c_str(), {444, 81}, 50, 2, WHITE);
    drawStats();

    back_button.render();
    if (prevMapIndex != 4)
        continue_button.render();
}

