#ifndef GAME_H
#define GAME_H

#include <memory>
#include "./Resources/StateManager.h"
#include "./Resources/SoundManager.h"


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
    Player *character; 
    MyCamera2D *myCam; 

    IPowerUpCreator *powerUpCreator; 
    PowerUp *item; 
private:
    Game();
    ~Game();

    void processInput();
    void update(float deltaTime);
    void render();
    bool isRunning;
    StateManager stateManager;
    SoundManager soundManager;
};

#endif
