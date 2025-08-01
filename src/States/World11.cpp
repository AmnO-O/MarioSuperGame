#include "States/World11.h"
#include "Game.h"
#include "Resources/ResourceManager.h"
#include <raylib.h>

World1_1::World1_1() 
{
    isRunning = true;
	Images::loadAllTextures("../assets/levelImages/");

    character = new Player(CharacterType::MARIO, {  100, 100 });
    character->setGroundLevel(2.0f * GetScreenHeight());

    maps.push_back(Map("../assets/maps/1-1/", Images::textures["mapobject.png"]));
    maps[currentMap].SetUp(cm, character);

    myCam = new MyCamera2D(1.0f * GetScreenWidth(), 1.0f * GetScreenHeight()); 
    myCam->setMapSize(maps[currentMap].getSize());
    
    powerUpCreator = new NormalMushroomCreator(); 
    item = powerUpCreator->create({350, 100}); 
    item -> setGroundLevel(205);
}

World1_1::~World1_1() 
{
    Images::unloadAllTextures();
    for (int i = 0; i < maps.size(); i++)
        maps[i].Unload();
    
    delete character; 
    delete myCam; 
    delete item; 
    delete powerUpCreator; 
}

void World1_1::update(float deltaTime) 
{
    cm.CheckAllCollisions();
    maps[currentMap].Update(deltaTime);

    if(deltaTime < 0.2) 
        character->update(deltaTime); 

    myCam -> update(character); 
    item->update(deltaTime);
    
    if(CheckCollisionRecs(character->getHitbox(), item->getHitbox())){
        item->applyEffect(character); 
    }
}

void World1_1::render() 
{
    Camera2D camera = myCam ->getCamera(); 
    //BeginDrawing();
    //ClearBackground(RAYWHITE);

    /// camera draw here

        BeginMode2D(camera); 
        maps[currentMap].Draw();
        if(character)
            character->render(); 

        if(item)
            item->render(); 
        EndMode2D(); 


    //EndDrawing();
}
