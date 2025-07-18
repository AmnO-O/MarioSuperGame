#include "SoundManager.h"

void SoundManager::loadMenuSound()
{
    InitAudioDevice();
    menuSound = LoadMusicStream(menu_filePath.c_str());
    SetMusicVolume(menuSound, volume);
}

void SoundManager::playMenuSound()
{
    PlayMusicStream(menuSound);
}

void SoundManager::stopMenuSound()
{
    StopMusicStream(menuSound);
    UnloadMusicStream(menuSound);
    CloseAudioDevice();
}

void SoundManager::updateMenuSound()
{
    UpdateMusicStream(menuSound);
}
