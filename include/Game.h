#ifndef GAME_H
#define GAME_H

#include "Character/Character.h"
#include "Character/MyCamera2D.h"
#include <vector>
#include "Map.hpp"

class Game {
public:
    static Game& getInstance();
    void run();

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    Game(Game&&) = delete;
    Game& operator=(Game&&) = delete;
private:

    std::vector<Map> maps = {};
    Character *character; 
    MyCamera2D *myCam; 
    int currentMap = 0;
    Game();
    ~Game();

    void processInput();
    void update(float deltaTime);
    void render();
    bool isRunning;
};

#endif
