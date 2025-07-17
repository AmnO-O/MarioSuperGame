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
    InitWindow(1600, 900, "Mario Game");
    SetTargetFPS(60);
    isRunning = true;

    currentState = std::make_unique<MainMenu>([this](std::unique_ptr<MenuState> newState) {
        switchState(std::move(newState));
    });
}

Game::~Game() {
    currentState->unload();
    CloseWindow();
}

void Game::switchState(std::unique_ptr<MenuState> newState)
{
    currentState->unload();
    currentState = std::move(newState);
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
    currentState->update(deltaTime);
}

void Game::render() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    currentState->render();
    EndDrawing();
}
