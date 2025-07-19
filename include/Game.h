#ifndef GAME_H
#define GAME_H

#include "Character/Character.h"

class Game {
public:
    static Game& getInstance();
    void run();

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    Game(Game&&) = delete;
    Game& operator=(Game&&) = delete;
    Character *character; 
private:
    Game();
    ~Game();

    void processInput();
    void update(float deltaTime);
    void render();

    bool isRunning;
};

#endif
