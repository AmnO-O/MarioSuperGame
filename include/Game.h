#ifndef GAME_H
#define GAME_H

#include <memory>
#include "MainMenu.h"

class Game {
public:
    static Game& getInstance();

    void switchState(std::unique_ptr<MenuState> newState);
    void run();

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    Game(Game&&) = delete;
    Game& operator=(Game&&) = delete;

private:
    Game();
    ~Game();

    void processInput();
    void update(float deltaTime);
    void render();

    bool isRunning;
    std::unique_ptr<MenuState> currentState;
};

#endif
