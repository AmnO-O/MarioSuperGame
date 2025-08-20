#include "Resources/StatsManager.h"
#include <fstream>

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
    lastScore = amount;
    scoreTimer = duration; 
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
    if (scoreTimer > 0.0f)
        scoreTimer -= deltaTime;
}

