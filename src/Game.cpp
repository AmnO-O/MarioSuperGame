#include "Game.h"
#include "ResourceManager.h"
#include "raylib.h"

// Singleton instance
Game& Game::getInstance() {
    static Game instance;
    return instance;
}

Game::Game() {
    InitWindow(1440, 810, "Mario Game");
    SetTargetFPS(60);
    isRunning = true;
	Images::loadAllTextures("assets/images/");
    character = new Character(CharacterType::MARIO, { 100, 100 });
}

Game::~Game() {
    CloseWindow();
    delete character; 
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
    character->update(deltaTime); 
}

void Game::render() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText("Hello Mario", 350, 280, 20, DARKGRAY);
    if(character)
        character->render(); 

    EndDrawing();
}
