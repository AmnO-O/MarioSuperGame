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
    character = new Character(CharacterType::MARIO, {  100, 100 });
    myCam = new MyCamera2D(1600.0f, 900.0f); 
}

Game::~Game() {
    CloseWindow();
    delete character; 
    delete myCam; 
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
    myCam -> update(character->getPosition()); 
    myCam->setZoom(5); 
}

void Game::render() {
    Camera2D camera = myCam ->getCamera(); 
    BeginDrawing();
    ClearBackground(RAYWHITE);

    /// camera draw here

        BeginMode2D(camera); 
            if(character)
                character->render(); 
        EndMode2D(); 


    DrawText("Hello Mario", 350, 280, 20, DARKGRAY);


    EndDrawing();
}
