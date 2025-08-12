#include "States/World.h"
#include "States/MainMenu.h"
#include "States/LevelMenu.h"
#include "States/GameOverMenu.h"
#include "Game.h"
#include "Resources/ResourceManager.h"
#include <raylib.h>
#include "Character/Character.h"

World::World(bool checkMario, int index, float time)
  : popup_menu(),
    mapIndex(index),
    time_level(time),
    isMario(checkMario),
    score_number(0),
    number_of_coins(0),
    settings_button("assets/images/setting.png", {25, 27, 100, 100}, [&]() {
        popup_menu.toggle();
    }),
    settings_button_state(LoadTexture("assets/images/setting_red.png")),
    coin_display(LoadTexture("assets/images/coin_display.png"))
{
    isRunning = true;

	Images::loadAllTextures("assets/images/");
    font = LoadFont("assets/fonts/SuperMarioBros.ttf");

    if (checkMario)
        character = new Player(CharacterType::MARIO, {  100, 100 });
    else
        character = new Player(CharacterType::LUIGI, { 100, 100 });

    if (mapIndex == 1)
        currentMap = new Map("assets/maps/1-1/", Images::textures["mapobject.png"]);
    if (mapIndex == 2)
        currentMap = new Map("assets/maps/1-2/", Images::textures["mapobject.png"]);

    currentMap->SetUp(character);
    Timer::getInstance().setup(time_level);
}

World::~World() 
{
    Images::unloadAllTextures();
    currentMap->Unload();

    UnloadTexture(settings_button_state);
    UnloadTexture(coin_display);

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

void World::drawStats()
{
    std::string charType; 
    if (isMario)
        charType = "MARIO";
    else
        charType = "LUIGI";

    DrawTextEx(font, charType.c_str(), {203, 33}, 40, 2, WHITE);

    int maxDigit = 6;
    int scoreDigits = (int)std::to_string(score_number).length();
    std::string scoreStr;

    if (scoreDigits <= maxDigit)
    {
        int remaining = maxDigit - scoreDigits;
        for (int i=0; i<remaining; i++)
            scoreStr += "0";

        scoreStr += std::to_string(score_number);
    }

    DrawTextEx(font, scoreStr.c_str(), {203, 86}, 40, 2, WHITE);

    DrawTexture(coin_display, 614, 79, WHITE);
    int maxCoinsDigits = 2;
    int coinsDigits = (int)std::to_string(number_of_coins).length();
    std::string coinsStr  = ":";

    if (coinsDigits <= maxCoinsDigits)
    {
        int remaining = maxCoinsDigits - coinsDigits;
        for (int i=0; i<remaining; i++)
            coinsStr += "0";

        coinsStr += std::to_string(number_of_coins);
    }

    DrawTextEx(font, coinsStr.c_str(), {660, 86}, 40, 2, WHITE);


    std::string w = "WORLD"; std::string title;
    DrawTextEx(font, w.c_str(), {941, 33}, 40, 2, WHITE);

    if (mapIndex == 1)
        title = "1-1";
    else if (mapIndex == 2)
        title = "1-2";
    else if (mapIndex == 3)
        title = "1-3";
    else if (mapIndex == 4)
        title = "1-4";
    
    DrawTextEx(font, title.c_str(), {984, 86}, 40, 2, WHITE);

    std::string time = "TIME";
    DrawTextEx(font, time.c_str(), {1308, 33}, 40, 2, WHITE);   
    int totalSec = (int)floorf(Timer::getInstance().remaining + 0.0001f); // small epsilon for safety
    int mins = totalSec / 60;
    int secs = totalSec % 60;

    std::string timeDisplay = (mins < 10 ? "0" : "") + std::to_string(mins) + ":" + (secs < 10 ? "0" : "") + std::to_string(secs);
    DrawTextEx(font, timeDisplay.c_str(), {1300, 86}, 40, 2, Timer::getInstance().time_color);
}

void World::saveGame(const std::string& filename) const
{
    std::ofstream fout(filename);
    if (!fout.is_open()) 
        std::throw_with_nested(std::runtime_error("Failed to open save file"));

    fout << (isMario ? "MARIO" : "LUIGI") << '\n';
    fout << mapIndex << '\n';
    fout << character->getPosition().x << ' ' << character->getPosition().y << '\n';
    fout << score_number << '\n';
    fout << number_of_coins << '\n';
    fout << Timer::getInstance().remaining << '\n';
    // Add more as needed

    // player_data
    character->printData(fout); 

    

    fout.close();
}


void World::processInput()
{
    if (IsKeyPressed(KEY_P))
        popup_menu.toggle();
}

void World::update(float deltaTime) 
{    
    if (!hasUpdated)
    {
        hasUpdated = true;
        return;
    }
    
    if (currentMap->isEnd()) {
        StateManager::getInstance().pushState(std::make_unique<LevelMenu>(isMario));
        ResumeMusicStream(SoundManager::getInstance().playMusic);
    }
  
    if (!SoundManager::getInstance().death_played)
        processInput();

    if ((SoundManager::getInstance().death_played && !IsSoundPlaying(SoundManager::getInstance().deathSound)) 
    || (Timer::getInstance().remaining <= 0.0f))
	{
        if (IsMusicStreamPlaying(SoundManager::getInstance().playMusic))
            StopMusicStream(SoundManager::getInstance().playMusic);

        PlaySound(SoundManager::getInstance().gameOverSound);
		StateManager::getInstance().pushState(std::make_unique<GameOverMenu>(mapIndex, isMario));
		SoundManager::getInstance().game_over_played = true;
	}
    
    if (!popup_menu.isVisible)
    {
        if(deltaTime < 0.2) 
            currentMap->Update(deltaTime);

        Timer::getInstance().update(deltaTime);
        
        if (!SoundManager::getInstance().death_played)
            settings_button.update(deltaTime);
    }

    if (popup_menu.isVisible)
        popup_menu.update(deltaTime);
    
    number_of_coins = StatsManager::getInstance().getCoins();
    score_number = StatsManager::getInstance().getScore();
}

void World::render() 
{
    currentMap->Draw();

    settings_button.render();

    if (!popup_menu.isVisible)
    {
        bool isHovered = CheckCollisionPointRec(GetMousePosition(), settings_button.getBounds());
        if (isHovered && !SoundManager::getInstance().death_played)
            DrawTexture(settings_button_state, 25, 27, WHITE);
    }

    if (popup_menu.isVisible)
        popup_menu.render();

    drawStats();
}
