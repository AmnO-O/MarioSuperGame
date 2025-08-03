#ifndef GAME_H
#define GAME_H

#include "Character/Character.h"
#include "MyCamera2D.h"
#include <vector>
#include "Map.h"
#include "Observer/Observer.h"
#include "Object/Creator.h"

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
    int currentMap = 0;
    Player *character; 
    MyCamera2D *myCam; 
    
private:
    Game();
    ~Game();

    void processInput();
    void update(float deltaTime);
    void render();
    bool isRunning;
};

#endif
