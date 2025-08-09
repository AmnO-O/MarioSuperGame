#include "States/World.h"
#include "States/MainMenu.h"
#include "States/LevelMenu.h"
#include "States/GameOverMenu.h"
#include "Game.h"
#include "Resources/ResourceManager.h"
#include <raylib.h>
#include "Character/Character.h"

World::World(bool checkMario, int index)
  : popup_menu(),
    mapIndex(index),
    isMario(checkMario),
    settings_button("assets/images/setting.png", {25, 27, 100, 100}, [&]() {
        popup_menu.toggle();
    }),
    settings_button_state(LoadTexture("assets/images/setting_red.png"))
{
    isRunning = true;

	Images::loadAllTextures("assets/images/");

    if (checkMario)
        character = new Player(CharacterType::MARIO, {  100, 100 });
    else
        character = new Player(CharacterType::LUIGI, { 100, 100 });

    if (mapIndex == 1)
    {
        currentMap = new Map("assets/maps/1-1/", Images::textures["mapobject.png"]);
    }

    currentMap->SetUp(character);
}

World::~World() 
{
    Images::unloadAllTextures();
    currentMap->Unload();

    UnloadTexture(settings_button_state);

    delete character; 
}

bool World::getIsMario() const
{
    return isMario;
}

int World::getMapIndex() const
{
    return mapIndex;
}

void World::processInput()
{
    if (IsKeyPressed(KEY_P))
        popup_menu.toggle();
}

void World::update(float deltaTime) 
{
    if (currentMap->isEnd()) {
        StateManager::getInstance().pushState(std::make_unique<LevelMenu>(isMario));
        ResumeMusicStream(SoundManager::getInstance().playMusic);
    }

    if (!SoundManager::getInstance().death_played)
        processInput();

    if ((SoundManager::getInstance().death_played && !IsSoundPlaying(SoundManager::getInstance().deathSound)))
	{
        PlaySound(SoundManager::getInstance().gameOverSound);
		StateManager::getInstance().pushState(std::make_unique<GameOverMenu>());
		SoundManager::getInstance().game_over_played = true;
	}
    
    if (!popup_menu.isVisible)
    {
        if(deltaTime < 0.2) 
        {
            currentMap->Update(deltaTime);
        }
    }
        
    if (!popup_menu.isVisible)
        settings_button.update(deltaTime);

    if (popup_menu.isVisible)
        popup_menu.update(deltaTime);
}

void World::render() 
{
    currentMap->Draw();

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

