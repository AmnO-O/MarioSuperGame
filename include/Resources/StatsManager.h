#ifndef STATS_MANAGER_H
#define STATS_MANAGER_H

#include <string>

class StatsManager
{
    private:

        StatsManager() = default;
        StatsManager(const StatsManager&) = delete;
        StatsManager& operator=(const StatsManager&) = delete;

        int score;
        int coins;

    public:

        float time_taken; 
        static StatsManager& getInstance();

        int lastScore = 0;
        float scoreTimer = 0.0f;
        float duration = 1.0f;
        
        int getHighScore();
        void setHighScore(int newHigh);
        std::string getPath();
        void reset();
        void setStats(int newScore, int newCoins);
        void addScore(int amount);
        void addCoins();  
        int getScore() const;
        int getCoins() const;   
        
        void update(float deltaTime);
};

#endif