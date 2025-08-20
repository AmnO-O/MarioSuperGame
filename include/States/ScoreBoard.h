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

    Color backgroundColor      = { 245, 245, 245, 255 }; // Off-white (#F5F5F5), dịu hơn
    Color headerColor          = { 218, 165, 32, 255 };  // GoldenRod (#DAA520), vàng đậm hơn
    Color primaryTextColor     = BLACK; 
    Color secondaryTextColor = BLACK;
    Color accentColor = { 255, 100, 100, 255 };

    Font textfont, headerfont; 
private: 
    void loadScoresFromFile(std::string filePath);
    void printScoresToFile(std::string filePath);
    void appendScoreToFile(const ScoreRecord &record, std::string filePath); 
    void sortScores(); 
    std::string getCurrentDate();
    void renderBackground(); 
    void renderTabs(); 
    void DrawCurrentMapScoreboard();
    void DrawMapStats(const std::vector<ScoreRecord>& mapScores, float y);

    std::vector<ScoreRecord> GetMapScores(int map) const; 
        std::string FormatScore(int score) {
        std::string scoreStr = std::to_string(score);
        int insertPos = (int)scoreStr.length() - 3;
        while (insertPos > 0) {
            scoreStr.insert(insertPos, ",");
            insertPos -= 3;
        }
        return scoreStr;
    }

    ScoreBoardManager(); 
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
    Texture2D sub_background;

public: 
    ScoreBoard(); 
    ~ScoreBoard();

    void processInput() override;
    void update(float deltaTime) override;
    void render() override;
}; 