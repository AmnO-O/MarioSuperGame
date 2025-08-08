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
    SoundManager::getInstance().loadAllSounds("assets/sounds/");
    
    SoundManager::getInstance().playMusic = LoadMusicStream("assets/sounds/SuperMarioBros_theme_song.mp3");
    SetMusicVolume(SoundManager::getInstance().playMusic, SoundManager::getInstance().getVolume());

    SoundManager::getInstance().deathSound = LoadSound("assets/sounds/death.wav");
    SoundManager::getInstance().gameOverSound = LoadSound("assets/sounds/gameOver.wav");

    StateManager::getInstance().pushState(std::make_unique<MainMenu>());
}

Game::~Game() {
    SoundManager::getInstance().unloadAllSounds();
    UnloadMusicStream(SoundManager::getInstance().playMusic);
    UnloadSound(SoundManager::getInstance().deathSound);
    UnloadSound(SoundManager::getInstance().gameOverSound);
    
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
