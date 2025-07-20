#include "Game.h"
#include "ResourceManager.h"
#include "raylib.h"
#include "MainMenu.h"

// Singleton instance
Game& Game::getInstance() {
    static Game instance;
    return instance;
}

Game::Game() {
    InitWindow(1600, 900, "Mario Game");
    SetTargetFPS(60);
    isRunning = true;

    soundManager.loadMenuSound();

    stateManager.pushState(std::make_unique<MainMenu>(stateManager));
}

Game::~Game() {
    soundManager.stopMenuSound();
    
    while (stateManager.getCurrentState()) {
        stateManager.popState();
    }
    CloseWindow();
}

void Game::run() {
    soundManager.playMenuSound();
    
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
    soundManager.updateMenuSound();
    stateManager.update(deltaTime);
}

void Game::render() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    stateManager.render();
    EndDrawing();
}
