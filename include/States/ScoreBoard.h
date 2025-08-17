#pragma once
#include "raylib.h"
#include "../Resources/StateManager.h"
#include <vector>
#include <string>
#include "../Widgets/Button.h"


struct ScoreRecord{
    std::string playerName; 
    std::string date; 
    int map ; 
    int score; 
    
    ScoreRecord(const std::string &name, const std::string &date, int map, int score):
        playerName(name), date(date), map(map), score(score) {}
}; 

class ScoreBoardManager{
private:
    int currentMap = 1; 
    std::vector<ScoreRecord> allScores;
    std::string mapNames[4] = {
        "Grass Plains",
        "Underground Caves",
        "Sky Castle",
        "Lava World"
    };

    Color mapThemes[4] = {
        {34, 139, 34, 255},   // Forest Green for Grass Plains
        {139, 69, 19, 255},   // Saddle Brown for Underground
        {135, 206, 235, 255}, // Sky Blue for Sky Castle
        {178, 34, 34, 255}    // Fire Brick for Lava World
    };

    Color backgroundColor = { 25, 25, 35, 240 };
    Color headerColor = { 255, 215, 0, 255 }; // Gold
    Color primaryTextColor = { 255, 255, 255, 255 };
    Color secondaryTextColor = { 200, 200, 200, 255 };
    Color accentColor = { 255, 100, 100, 255 };
private: 
    void loadScoresFromFile(std::string filePath);
    void printScoresToFile(std::string filePath);
    void appendScoreToFile(const ScoreRecord &record, std::string filePath); 
    void sortScores(); 
    std::string getCurrentDate();
    ScoreBoardManager(); 
    void renderBackground(); 
public: 
    static ScoreBoardManager& getInstance(){
        static ScoreBoardManager instance; 
        return instance; 
    }
    
    ScoreBoardManager(const ScoreBoardManager&) = delete; 
    ScoreBoardManager& operator=(const ScoreBoardManager&) = delete;
    ~ScoreBoardManager();


    void addScore(const std::string &playerName, int map, int score);
    void update(float deltaTime);
    void render();
}; 


class ScoreBoard : public GameState{
private: 
    ImageButton return_button;
    Texture2D return_button_state;
public: 
    ScoreBoard(); 
    ~ScoreBoard();

    void processInput() override;
    void update(float deltaTime) override;
    void render() override;
}; 