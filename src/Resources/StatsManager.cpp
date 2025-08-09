#include "Resources/StatsManager.h"

StatsManager& StatsManager::getInstance() 
{
    static StatsManager instance;
    return instance;
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