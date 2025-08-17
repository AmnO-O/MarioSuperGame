#include "States/ScoreBoard.h"
#include <fstream>
#include <algorithm>
#include <ctime>
#include <sstream>
#include "States/MainMenu.h"

ScoreBoardManager::ScoreBoardManager(){
    loadScoresFromFile("assets/scores.txt");
    sortScores();
}

ScoreBoardManager::~ScoreBoardManager() {}

ScoreBoard::ScoreBoard() : return_button("assets/images/turn_back_white.png", {25, 27, 100, 100}, [&]() {
        StateManager::getInstance().pushState(std::make_unique<MainMenu>());
    }){
    return_button_state = LoadTexture("assets/images/turn_back_red.png");
}

ScoreBoard::~ScoreBoard() {
    UnloadTexture(return_button_state);
}



void ScoreBoardManager::loadScoresFromFile(std::string filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        return; 
    }

    std::string line;
    
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string playerName, date;
        int map, score;
        if (iss >> playerName >> date >> map >> score) {
            allScores.emplace_back(playerName, date, map, score);
        }
    }
    file.close();
}


void ScoreBoardManager::printScoresToFile(std::string filePath) {
    std::ofstream file(filePath);
    if (!file.is_open()) {
        return; 
    }

    for (const auto& record : allScores) {
        file << record.playerName << " " << record.date << " "
             << record.map << " " << record.score << "\n";
    }
    file.close();
}

void ScoreBoardManager::appendScoreToFile(const ScoreRecord &record, std::string filePath) {
    std::ofstream file(filePath, std::ios::app);
    if (file.is_open()) {
        file << record.playerName << " " << record.date << " "
                << record.map << " " << record.score << "\n";
        file.close();
    }
}

std::string ScoreBoardManager::getCurrentDate() {
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);
    
    std::ostringstream oss;
    oss << (localTime->tm_year + 1900) << '-'
        << (localTime->tm_mon + 1) << '-'
        << localTime->tm_mday;
    
    return oss.str();
}

void ScoreBoardManager::addScore(const std::string &playerName, int map, int score) {
    std::string date = getCurrentDate();
    allScores.emplace_back(playerName, date, map, score);
    appendScoreToFile(allScores.back(), "assets/scores.txt"); 
    sortScores();
}

void ScoreBoardManager::sortScores() {
    std::sort(allScores.begin(), allScores.end(), [](const ScoreRecord &a, const ScoreRecord &b) {
        return a.score > b.score;
    });
}

void ScoreBoardManager::update(float deltaTime) {
    if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {
        currentMap = (currentMap == 1) ? 4 : currentMap - 1;
    }
    if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) {
        currentMap = (currentMap == 4) ? 1 : currentMap + 1;
    }

    for (int i = 1; i <= 4; i++) {
        if (IsKeyPressed(KEY_ONE + i - 1)) {
            currentMap = i;
        }
    }
}

void ScoreBoardManager::renderBackground(){
    Color theme = mapThemes[currentMap - 1];
    Color bgTop = { (unsigned char)(theme.r * 0.1f), (unsigned char)(theme.g * 0.1f), (unsigned char)(theme.b * 0.1f), 255 };
    Color bgBottom = { (unsigned char)(theme.r * 0.2f), (unsigned char)(theme.g * 0.2f), (unsigned char)(theme.b * 0.2f), 255 };

    DrawRectangleGradientV(0, 0, 1600, 900, bgTop, bgBottom);

    for (int i = 0; i < 15; i++) {
        float x = (i * 107) % 1600;
        float y = 50 + (i * 37) % 800;
        DrawCircleV({ x, y }, 4, { theme.r, theme.g, theme.b, 40 });
    }

    Rectangle panel = { 150, 80, 1300, 740 };
    DrawRectangleRounded(panel, 0.02f, 20, backgroundColor);
    DrawRectangleRoundedLines(panel, 0.02f, 20, 3, mapThemes[currentMap - 1]);
}

void ScoreBoardManager::render(){
    renderBackground(); 

}


void ScoreBoard::processInput() {

}

void ScoreBoard::update(float deltaTime) {
    return_button.update(deltaTime); 
    ScoreBoardManager::getInstance().update(deltaTime); 
}


void ScoreBoard::render(){
    return_button.render();
    ScoreBoardManager::getInstance().render();
    
}
