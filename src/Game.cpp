#include "Game.h"
#include "ResourceManager.h"
#include "raylib.h"
#include "MainMenu.h"
#include "Button.h"

// Singleton instance
Game& Game::getInstance() {
    static Game instance;
    return instance;
}

Game::Game() {
    InitWindow(1024, 960, "Mario Game");
    SetTargetFPS(60);
    isRunning = true;

    mainMenu = std::make_unique<MainMenu>();
}

Game::~Game() {
    mainMenu->unload();
    CloseWindow();
}

void Game::run() {
    while (!WindowShouldClose() && isRunning) {
        float deltaTime = GetFrameTime();

        processInput();
        update(deltaTime);
        render();
    }
}

void Game::processInput() {
    if (IsKeyPressed(KEY_ESCAPE)) {
        isRunning = false;
    }
}

void Game::update(float deltaTime) {
    mainMenu->update(deltaTime);
}

void Game::render() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    mainMenu->render();

    EndDrawing();
}
