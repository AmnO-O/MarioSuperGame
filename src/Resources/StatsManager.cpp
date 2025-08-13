#include "Resources/StatsManager.h"
#include <fstream>

StatsManager& StatsManager::getInstance() 
{
    static StatsManager instance;
    return instance;
}

int StatsManager::getHighScore()
{
    return high_score;
}

void StatsManager::setHighScore(int newHigh)
{
    if (newHigh > high_score) 
        high_score = newHigh;
}

std::string StatsManager::getPath()
{
    return high_score_path;
}

void StatsManager::reset() 
{
    score = 0;
    coins = 0;
}   

void StatsManager::setStats(int newScore, int newCoins) 
{
    score = newScore;
    coins = newCoins;
}

void StatsManager::addScore(int amount)
{
    score += amount;
}

void StatsManager::addCoins()
{
    coins++;
}

int StatsManager::getScore() const
{
    return score;
}

int StatsManager::getCoins() const
{
    return coins;
}

void StatsManager::update(float deltaTime)
{
    std::ifstream fin(high_score_path);
    if (fin.is_open()) 
    {
        int h;
        fin >> h;

        if (h > 999999)
            high_score = 999999;
        else
            high_score = h;

        fin.close();
    }

    else
        high_score = 0; 
}

