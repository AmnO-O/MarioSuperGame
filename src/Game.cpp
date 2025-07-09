#include "Game.h"
#include "ResourceManager.h"
#include "raylib.h"

Game::Game() {
    InitWindow(1440, 810, "Mario Game");
    SetTargetFPS(60);
    isRunning = true;
}

Game::~Game() {
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
}

void Game::render() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText("Hello Mario", 350, 280, 20, DARKGRAY);

    EndDrawing();
}
