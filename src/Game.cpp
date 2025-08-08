#include "Game.h"
#include "Resources/ResourceManager.h"
#include "raylib.h"
#include "States/MainMenu.h"
#include <iostream>

// Singleton instance
Game& Game::getInstance() {
    static Game instance;
    return instance;
}

Game::Game() {
    InitWindow(1600, 900, "Mario Game");
    SetTargetFPS(60);
    isRunning = true;
    
    InitAudioDevice();
    SoundManager::getInstance().loadAll();

    StateManager::getInstance().pushState(std::make_unique<MainMenu>());
}

Game::~Game() {
    SoundManager::getInstance().unloadAll();
    
    while (StateManager::getInstance().getCurrentState()) {
        StateManager::getInstance().popState();
    }

    CloseAudioDevice();
    CloseWindow();
}

void Game::run() {
    SoundManager::getInstance().playMusic.looping = true;
    PlayMusicStream(SoundManager::getInstance().playMusic);

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
 
    UpdateMusicStream(SoundManager::getInstance().playMusic);
    StateManager::getInstance().update(deltaTime);
}

void Game::render() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    
    StateManager::getInstance().render();
    EndDrawing();
}
