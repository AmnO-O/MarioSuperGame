#include "States/ScoreBoard.h"
#include <fstream>
#include <algorithm>
#include <ctime>
#include <sstream>
#include "States/MainMenu.h"

ScoreBoardManager::ScoreBoardManager(){
    textfont = LoadFont("assets/fonts/LilitaOne-Regular.ttf");
    headerfont = LoadFont("assets/fonts/SuperMarioBros.ttf");
    loadScoresFromFile("data/scoreboard.txt");
    sortScores();
}

ScoreBoardManager::~ScoreBoardManager() {
    UnloadFont(textfont);
    UnloadFont(headerfont);
    allScores.clear();
}

ScoreBoard::ScoreBoard() : return_button("assets/images/turn_back_white.png", {25, 27, 100, 100}, [&]() {
        StateManager::getInstance().pushState(std::make_unique<MainMenu>());
    }){
    return_button_state = LoadTexture("assets/images/turn_back_red.png");
    sub_background = LoadTexture("assets/images/sub_menu_background.png");
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
    appendScoreToFile(allScores.back(), "data/scoreboard.txt"); 
    sortScores();
}

void ScoreBoardManager::sortScores() {
    std::sort(allScores.begin(), allScores.end(), [](const ScoreRecord &a, const ScoreRecord &b) {
        return a.score > b.score;
    });
}

std::vector<ScoreRecord> ScoreBoardManager::GetMapScores(int map) const {
    std::vector<ScoreRecord> mapScores;
    for (const auto& record : allScores) {
        if (record.map == map) {
            mapScores.push_back(record);
        }
    }
    return mapScores;
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

  //  DrawRectangleGradientV(0, 0, 1600, 900, bgTop, bgBottom);

    for (int i = 0; i < 15; i++) {
        int x = (i * 107) % 1600;
        int y = 50 + (i * 37) % 800;
        DrawCircleV({ 1.0f * x, 1.0f * y }, 4, { theme.r, theme.g, theme.b, 40 });
    }

    Rectangle panel = { 150, 80, 1300, 740 };
    DrawRectangleRounded(panel, 0.02f, 20, backgroundColor);
    DrawRectangleRoundedLines(panel, 0.02f, 20, 3, mapThemes[currentMap - 1]);
}

void ScoreBoardManager::renderTabs() {
    float tabWidth = 280;
    float tabHeight = 60;
    float startX = 200;
    float tabY = 90;

    for (int i = 0; i < 4; i++) {
        float tabX = startX + i * (tabWidth + 20);

        // Tab background
        Color tabColor = (i + 1 == currentMap) ? mapThemes[i] : Color{ 60, 60, 70, 255 };
        DrawRectangleRounded({ tabX, tabY, tabWidth, tabHeight }, 0.15f, 10, tabColor);

        if (i + 1 == currentMap) {
            DrawRectangleRoundedLines({ tabX, tabY, tabWidth, tabHeight }, 0.15f, 10, 2, headerColor);
        }

        // Map number
        std::string mapNum = std::to_string(i + 1);
        Vector2 numSize = MeasureTextEx(textfont, mapNum.c_str(), 24, 1);
        DrawTextEx(textfont, mapNum.c_str(),
            { tabX + 20, tabY + 10 }, 24, 1,
            (i + 1 == currentMap) ? primaryTextColor : secondaryTextColor);

        // Map name
        Vector2 nameSize = MeasureTextEx(headerfont, mapNames[i].c_str(), 16, 1);
        DrawTextEx(textfont, mapNames[i].c_str(),
            { tabX + 20, tabY + 35 }, 16, 1,
            (i + 1 == currentMap) ? primaryTextColor : secondaryTextColor);

        // Score count for this map
        std::vector<ScoreRecord> mapScores = GetMapScores(i + 1);
        std::string countStr = "(" + std::to_string(mapScores.size()) + " scores)";
        DrawTextEx(textfont, countStr.c_str(),
            { tabX + tabWidth - 90, tabY + 35 }, 14, 1, secondaryTextColor);
    }
}

void ScoreBoardManager::DrawCurrentMapScoreboard() {
    std::vector<ScoreRecord> mapScores = GetMapScores(currentMap);

    // Title
    std::string title = "MAP " + std::to_string(currentMap) + " - " + mapNames[currentMap - 1];
    Vector2 titleSize = MeasureTextEx(headerfont, title.c_str(), 36, 2);
    Vector2 titlePos = { 800 - titleSize.x / 2, 180 };

    // Title shadow
    DrawTextEx(headerfont, title.c_str(), { titlePos.x + 2, titlePos.y + 2 }, 36, 2, { 0, 0, 0, 100 });
    DrawTextEx(headerfont, title.c_str(), titlePos, 36, 2, mapThemes[currentMap - 1]);

    // Headers
    float headerY = 240;
    DrawRectangle(200, (int)headerY - 5, 1200, 35, { 255, 255, 255, 20 });

    float panelLeft = GetScreenWidth()  * 0.125f; 
    float panelWidth = GetScreenWidth()  * 0.75f; 
    
    // Column positions - evenly distributed across panel width
    float columnSpacing = panelWidth / 4.0f; // Divide panel into 4 equal sections
    float rankX = panelLeft + columnSpacing * 0.1f; // 10% into first section
    float playerX = panelLeft + columnSpacing * 1.1f; // 10% into second section  
    float scoreX = panelLeft + columnSpacing * 2.1f; // 10% into third section
    float dateX = panelLeft + columnSpacing * 3.1f; // 10% into fourth section
    
    // Headers
    DrawRectangle((int)panelLeft, (int)headerY - 5, (int)panelWidth, 35, { 255, 255, 255, 20 });
    DrawTextEx(headerfont, "RANK", { rankX, headerY }, 22, 1, headerColor);
    DrawTextEx(headerfont, "PLAYER", { playerX, headerY }, 22, 1, headerColor);
    DrawTextEx(headerfont, "SCORE", { scoreX, headerY }, 22, 1, headerColor);
    DrawTextEx(headerfont, "DATE", { dateX, headerY }, 22, 1, headerColor);

    DrawRectangle(200, (int)headerY + 30, 1200, 2, mapThemes[currentMap - 1]);

    // Scores for current map
    float startY = 290;
    float rowHeight = 40;
    int displayCount = std::min((int)mapScores.size(), 10);

    if (mapScores.empty()) {
        std::string noScoresText = "No scores recorded for this map yet!";
        Vector2 noScoresSize = MeasureTextEx(textfont, noScoresText.c_str(), 30, 1);
        DrawTextEx(textfont, noScoresText.c_str(),
            { GetScreenWidth()  * 0.5f - noScoresSize.x * 0.5f, GetScreenHeight() * 0.389f }, 30, 1, secondaryTextColor);
        
        std::string firstRecordText = "Be the first to set a record!";
        Vector2 firstRecordSize = MeasureTextEx(textfont, firstRecordText.c_str(), 28, 1);
        DrawTextEx(textfont, firstRecordText.c_str(),
            { GetScreenWidth()  * 0.5f - firstRecordSize.x * 0.5f, GetScreenHeight()  * 0.422f }, 28, 1, secondaryTextColor);
    }

    for (int i = 0; i < displayCount; i++) {
        float y = startY + i * rowHeight;
        const ScoreRecord& entry = mapScores[i];

        // Row background
        if (i % 2 == 0) {
            DrawRectangle((int)panelLeft, (int)y - 5, (int)panelWidth, (int)rowHeight - 5, { 255, 255, 255, 10 });
        }

        // Rank highlighting
        Color rankColor = secondaryTextColor;
        float highlightX = panelLeft - GetScreenWidth() * 0.00625f; // 190/1600
        if (i == 0) {
            rankColor = { 255, 215, 0, 255 }; // Gold
            DrawRectangle((int)highlightX, (int)y - 5, 8, (int)rowHeight - 5, { 255, 215, 0, 255 });
        }
        else if (i == 1) {
            rankColor = { 192, 192, 192, 255 }; // Silver
            DrawRectangle((int)highlightX, (int)y - 5, 8, (int)rowHeight - 5, { 192, 192, 192, 255 });
        }
        else if (i == 2) {
            rankColor = { 205, 127, 50, 255 }; // Bronze
            DrawRectangle((int)highlightX, (int)y - 5, 8, (int)rowHeight - 5, { 205, 127, 50, 255 });
        }

        // Draw entry data using same column positions
        std::string rank = std::to_string(i + 1);
        DrawTextEx(textfont, rank.c_str(), { rankX, y }, 20, 1, rankColor);
        DrawTextEx(textfont, entry.playerName.c_str(), { playerX, y }, 20, 1, primaryTextColor);

        std::string scoreStr = FormatScore(entry.score);
        DrawTextEx(textfont, scoreStr.c_str(), { scoreX, y }, 20, 1, primaryTextColor);
        DrawTextEx(textfont, entry.date.c_str(), { dateX, y }, 20, 1, secondaryTextColor);
    }

    // Map statistics
    DrawMapStats(mapScores, startY + displayCount * rowHeight + 40);
}

void ScoreBoardManager::DrawMapStats(const std::vector<ScoreRecord>& mapScores, float y) {
    if (mapScores.empty()) return;

    DrawRectangle(200, (int)y, 1200, 80, { 255, 255, 255, 15 });

    // Statistics
    std::string totalScores = "Total Scores: " + std::to_string(mapScores.size());
    DrawTextEx(textfont, totalScores.c_str(), { 220, y + 15 }, 23, 1, secondaryTextColor);

    std::string highScore = "Best Score: " + FormatScore(mapScores[0].score) + " by " + mapScores[0].playerName;
    DrawTextEx(textfont, highScore.c_str(), { 220, y + 40 }, 23, 1, mapThemes[currentMap - 1]);

    // Average score
    if (mapScores.size() > 1) {
        int totalScore = 0;
        for (const auto& entry : mapScores) {
            totalScore += entry.score;
        }
        int avgScore = totalScore / (int)mapScores.size();
        std::string avgScoreStr = "Average: " + FormatScore(avgScore);
        DrawTextEx(textfont, avgScoreStr.c_str(), { 220, y + 62 }, 21, 1, secondaryTextColor);
    }
}


void ScoreBoardManager::render(){
    renderBackground(); 
    renderTabs(); 
    DrawCurrentMapScoreboard();
}


void ScoreBoard::processInput() {

}

void ScoreBoard::update(float deltaTime) {
    return_button.update(deltaTime); 
    ScoreBoardManager::getInstance().update(deltaTime); 
}


void ScoreBoard::render(){
    DrawTexture(sub_background, 0, 0, WHITE);
    return_button.render();
    ScoreBoardManager::getInstance().render();
    bool isHovered = CheckCollisionPointRec(GetMousePosition(), return_button.getBounds());
    
    if (isHovered)
        DrawTexture(return_button_state, 25, 27, WHITE);
}
