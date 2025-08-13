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
        int high_score;
        std::string high_score_path = "data/highscore.txt";

    public:

        float time_taken; 
        static StatsManager& getInstance();
        
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