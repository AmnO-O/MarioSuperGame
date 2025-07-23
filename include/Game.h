#ifndef GAME_H
#define GAME_H

#include "Character/Character.h"
#include "Character/MyCamera2D.h"
#include <vector>
#include "Map.h"
#include "Observer.h"

class Game {
public:
    static Game& getInstance();
    void run();

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    Game(Game&&) = delete;
    Game& operator=(Game&&) = delete;
private:

    CollisionManager cm;
    std::vector<Map> maps = {};
    int currentMap = 0;
    Character *character; 
    MyCamera2D *myCam; 
    Game();
    ~Game();

    void processInput();
    void update(float deltaTime);
    void render();
    bool isRunning;
};

#endif
