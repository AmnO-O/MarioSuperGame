#include "Game.h"
#include "./Resources/ResourceManager.h"
#include "raylib.h"
#include "./States/MainMenu.h"

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

    stateManager.pushState(std::make_unique<MainMenu>(stateManager, soundManager));
 

}

Game::~Game() {
    soundManager.unloadMenuSound();
    
    while (stateManager.getCurrentState()) {
        stateManager.popState();
    }
    CloseWindow();
    Images::unloadAllTextures();
    for (int i = 0; i < maps.size(); i++)
        maps[i].Unload();
    delete character; 
    delete myCam; 
    delete item; 
    delete powerUpCreator; 
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
