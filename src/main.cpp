#include "Game.h"
#include "raylib.h"

int main() {
    SetTraceLogLevel(LOG_NONE);
    Game::getInstance().run();
    return 0;
}