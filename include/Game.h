#ifndef GAME_H
#define GAME_H

#include <memory>
#include "./Resources/StateManager.h"
#include "./Resources/SoundManager.h"


#include "Character/Character.h"
#include "MyCamera2D.h"
#include <vector>
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
    Game();
    ~Game();

    void processInput();
    void update(float deltaTime);
    void render();
    bool isRunning;
    
};

#endif
