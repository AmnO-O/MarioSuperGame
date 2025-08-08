#include "States/World11.h"
#include "States/MainMenu.h"
#include "States/GameOverMenu.h"
#include "Game.h"
#include "Resources/ResourceManager.h"
#include <raylib.h>
#include "Character/Character.h"

World1_1::World1_1(bool checkMario)
  : popup_menu(),
    isMario(checkMario),
    settings_button("assets/images/setting.png", {25, 27, 100, 100}, [&]() {
        popup_menu.toggle();
    }),
    settings_button_state(LoadTexture("assets/images/setting_red.png"))
{
    isRunning = true;

	Images::loadAllTextures("assets/images/");


    character = new Player(CharacterType::MARIO, {  100, 100 });

    maps.push_back(Map("assets/maps/1-1/", Images::textures["mapobject.png"]));
    maps[currentMap].SetUp(character);

    myCam = new MyCamera2D(1.0f * GetScreenWidth(), 1.0f * GetScreenHeight()); 
    myCam->setMapSize(maps[currentMap].getSize());
}

World1_1::~World1_1() 
{
    Images::unloadAllTextures();
    for (int i = 0; i < maps.size(); i++)
        maps[i].Unload();
    
    UnloadTexture(settings_button_state);

    delete character; 
    delete myCam; 
}

bool World1_1::getIsMario() const
{
    return isMario;
}

void World1_1::processInput()
{
    if (IsKeyPressed(KEY_P))
        popup_menu.toggle();
}

void World1_1::update(float deltaTime) 
{
    if (!SoundManager::getInstance().death_played)
        processInput();

    if (SoundManager::getInstance().death_played && !IsSoundPlaying(SoundManager::getInstance().deathSound))
	{
		SoundManager::getInstance().playGameOverSound();
		StateManager::getInstance().pushState(std::make_unique<GameOverMenu>());
		SoundManager::getInstance().game_over_played = true;
	}
    
    if (!popup_menu.isVisible)
    {
        if(deltaTime < 0.2) {
            CollisionManager::getInstance().Register(character->shootFireball()); 
            CollisionManager::getInstance().CheckAllCollisions();
            maps[currentMap].Update(deltaTime);
            myCam -> update(character); 
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

    /// camera draw here
    BeginMode2D(camera); 
        maps[currentMap].Draw();
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
}

PopUpMenu1_1::PopUpMenu1_1()
  : isVisible(false),
    resume_button("RESUME", {663, 296, 330, 50}, WHITE, RED, [&](){
        toggle();
    }),
    restart_button("RESTART", {639, 392, 330, 50}, WHITE, RED, [&]() {
        restart();
    }),
    exit_button("EXIT", {710, 488, 330, 50}, WHITE, RED, [&]() {
        exitGame();
    }),
    save_button("SAVE GAME", {594, 584, 330, 50}, WHITE, RED, []() {

    }),
    frame({500, 225, 600, 472})
{

}

void PopUpMenu1_1::restart()
{
    bool isMario = dynamic_cast<World1_1*>(StateManager::getInstance().getCurrentState())->getIsMario();
    StateManager::getInstance().pushState(std::make_unique<World1_1>(isMario));
    SoundManager::getInstance().resumePlayMusic();
}

void PopUpMenu1_1::exitGame()
{
    StateManager::getInstance().pushState(std::make_unique<MainMenu>());
    SoundManager::getInstance().resumePlayMusic();
}

void PopUpMenu1_1::toggle()
{
    isVisible = !isVisible;

    if (isVisible)
        SoundManager::getInstance().pausePlayMusic();
    else
        SoundManager::getInstance().resumePlayMusic();
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