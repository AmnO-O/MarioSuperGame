#ifndef GAME_H
#define GAME_H

class Game {
public:
    Game();
    ~Game();
    void run();

private:
    void processInput();
    void update(float deltaTime);
    void render();

    bool isRunning;
};

#endif
