#include "Game.h"
#include "Resources/ResourceManager.h"
#include "raylib.h"
#include "States/MainMenu.h"

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
    SoundManager::getInstance().loadPlayMusic();
    SoundManager::getInstance().loadDeathSound();
    SoundManager::getInstance().loadGameOverSound();

    StateManager::getInstance().pushState(std::make_unique<MainMenu>());
}

Game::~Game() {
    SoundManager::getInstance().unloadPlayMusic();
    SoundManager::getInstance().unloadDeathSound();
    SoundManager::getInstance().unloadGameOverSound();
    
    while (StateManager::getInstance().getCurrentState()) {
        StateManager::getInstance().popState();
    }

    CloseAudioDevice();
    CloseWindow();
}

void Game::run() {
    SoundManager::getInstance().playMusic.looping = true;
    SoundManager::getInstance().playPlayMusic();

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

    SoundManager::getInstance().updatePlayMusic();

    StateManager::getInstance().update(deltaTime);
}

void Game::render() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    
    StateManager::getInstance().render();
    EndDrawing();
}
