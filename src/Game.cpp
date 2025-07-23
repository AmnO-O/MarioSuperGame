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
    character->setGroundLevel(200); 
    myCam = new MyCamera2D(1600.0f, 900.0f); 
    powerUpCreator = new StarCreator(); 
    item = powerUpCreator->create({150, 100}); 
    item -> setGroundLevel(200);
}

Game::~Game() {
    CloseWindow();
    delete character; 
    delete myCam; 
    delete item; 
    delete powerUpCreator; 
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
    if(deltaTime < 0.2) 
        character->update(deltaTime); 
    myCam->update(character->getPosition()); 
    item->update(deltaTime);
    

    if(CheckCollisionRecs(character->getHitbox(), item->getHitbox())){
        item->applyEffect(character); 
    }
}

void Game::render() {
    Camera2D camera = myCam ->getCamera(); 
    BeginDrawing();
    ClearBackground(RAYWHITE);

    /// camera draw here

        BeginMode2D(camera); 
            if(character)
                character->render(); 

            if(item)
                item->render(); 
        EndMode2D(); 


    DrawText("Hello Mario", 350, 280, 20, DARKGRAY);


    EndDrawing();
}
