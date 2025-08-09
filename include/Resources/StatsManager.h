#ifndef STATS_MANAGER_H
#define STATS_MANAGER_H

class StatsManager
{
    private:

        StatsManager() = default;
        StatsManager(const StatsManager&) = delete;
        StatsManager& operator=(const StatsManager&) = delete;

        int score;
        int coins;

    public:

        
        static StatsManager& getInstance();
        
        void reset();
        void setStats(int newScore, int newCoins);
        void addScore(int amount);
        void addCoins();  
        int getScore() const;
        int getCoins() const;
};

#endif