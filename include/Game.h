#ifndef GAME_H
#define GAME_H

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
