#include "Game.h"
#include "ResourceManager.h"
#include "raylib.h"

// Singleton instance
Game& Game::getInstance() {
    static Game instance;
    return instance;
}

Game::Game() {
    InitWindow(1600, 900, "Mario Game");
    SetTargetFPS(60);
    isRunning = true;
	Images::loadAllTextures("assets/images/");

    character = new Player(CharacterType::LUIGI, {  100, 100 });
    character->setGroundLevel(2.0f * GetScreenHeight());

    maps.push_back(Map("assets/maps/1-1/", Images::textures["mapobject.png"]));
    maps[currentMap].SetUp(character);

    myCam = new MyCamera2D(1.0f * GetScreenWidth(), 1.0f * GetScreenHeight()); 
    myCam->setMapSize(maps[currentMap].getSize());
}

Game::~Game() {
    CloseWindow();
    Images::unloadAllTextures();
    for (int i = 0; i < maps.size(); i++)
        maps[i].Unload();
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
    CollisionManager::getInstance().CheckAllCollisions();
    maps[currentMap].Update(deltaTime);

    myCam -> update(character); 
}

void Game::render() {
    Camera2D camera = myCam ->getCamera(); 
    BeginDrawing();
    ClearBackground(RAYWHITE);

    /// camera draw here

        BeginMode2D(camera); 
            maps[currentMap].Draw();
        EndMode2D(); 


    EndDrawing();
}
