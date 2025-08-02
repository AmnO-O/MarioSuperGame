#include "States/World11.h"
#include "Game.h"
#include "Resources/ResourceManager.h"
#include <raylib.h>

World1_1::World1_1(StateManager& stateManager, SoundManager& soundManager)
  : stateManager(stateManager),
    soundManager(soundManager),
    popup_menu(stateManager, soundManager),
    settings_button("assets/images/setting.png", {25, 27, 100, 100}, [&]() {
        popup_menu.toggle();
    }),
    settings_button_state(LoadTexture("assets/images/setting_red.png"))
{
    isRunning = true;

	Images::loadAllTextures("assets/images/");


    character = new Player(CharacterType::MARIO, {  100, 100 });
    character->setGroundLevel(2.0f * GetScreenHeight());

    maps.push_back(Map("assets/maps/1-1/", Images::textures["mapobject.png"]));
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
    
    UnloadTexture(settings_button_state);

    delete character; 
    delete myCam; 
    delete item; 
    delete powerUpCreator; 
}

void World1_1::processInput()
{
    if (IsKeyPressed(KEY_P))
        popup_menu.toggle();
}

void World1_1::update(float deltaTime) 
{
    processInput();

    if (!popup_menu.isVisible)
    {
        cm.addFireball(character->shootFireball()); 
        cm.CheckAllCollisions();
        maps[currentMap].Update(deltaTime);

        if(deltaTime < 0.2) 
                character->update(deltaTime); 

        myCam -> update(character); 
        item->update(deltaTime);

        if(CheckCollisionRecs(character->getHitbox(), item->getHitbox())) {
                item->applyEffect(character); 
        }
    }
        
    if (!popup_menu.isVisible)
        settings_button.update(deltaTime);

    if (popup_menu.isVisible)
        popup_menu.update(deltaTime);
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

    settings_button.render();

    if (!popup_menu.isVisible)
    {
        bool isHovered = CheckCollisionPointRec(GetMousePosition(), settings_button.getBounds());
        if (isHovered)
            DrawTexture(settings_button_state, 25, 27, WHITE);
    }

    if (popup_menu.isVisible)
        popup_menu.render();
    //EndDrawing();
}

PopUpMenu1_1::PopUpMenu1_1(StateManager& stateManager, SoundManager& soundManager)
  : isVisible(false),
    stateManager(stateManager),
    soundManager(soundManager),
    resume_button("RESUME", {663, 296, 330, 50}, WHITE, RED, [&](){
        toggle();
    }),
    restart_button("RESTART", {639, 392, 330, 50}, WHITE, RED, [&]() {
        restart(stateManager, soundManager);
    }),
    exit_button("EXIT", {710, 488, 330, 50}, WHITE, RED, [&]() {
        exitGame(stateManager);
    }),
    save_button("SAVE GAME", {594, 584, 330, 50}, WHITE, RED, []() {

    }),
    frame({500, 225, 600, 472})
{

}

void PopUpMenu1_1::restart(StateManager& stateManager, SoundManager& soundManager)
{
    stateManager.popState();
    stateManager.pushState(std::make_unique<World1_1>(stateManager, soundManager));
    soundManager.resumeMenuSound();
}

void PopUpMenu1_1::exitGame(StateManager& stateManager)
{
    stateManager.popState();
    soundManager.resumeMenuSound();
}

void PopUpMenu1_1::toggle()
{
    isVisible = !isVisible;

    if (isVisible)
        soundManager.pauseMenuSound();
    else
        soundManager.resumeMenuSound();
}

void PopUpMenu1_1::update(float deltaTime)
{
    if (isVisible)
    {
        resume_button.update(deltaTime);
        restart_button.update(deltaTime);
        exit_button.update(deltaTime);
        save_button.update(deltaTime);
    }

}

void PopUpMenu1_1::render()
{
    if (isVisible)
    {
        DrawRectangleRec(frame, Fade(BLACK, 0.8f));
        DrawRectangleLinesEx(frame, 5, WHITE);

        resume_button.render();
        restart_button.render();
        exit_button.render();
        save_button.render();
    }
}