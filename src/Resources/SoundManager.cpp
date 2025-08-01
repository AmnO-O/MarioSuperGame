#include "Resources/SoundManager.h"

void SoundManager::loadMenuSound()
{
    InitAudioDevice();
    menuSound = LoadMusicStream(menu_filePath.c_str());
    SetMusicVolume(menuSound, current_volume);
}

void SoundManager::playMenuSound()
{
    PlayMusicStream(menuSound);
}

void SoundManager::pauseMenuSound()
{
    PauseMusicStream(menuSound);
}

void SoundManager::resumeMenuSound()
{
    ResumeMusicStream(menuSound);
}

void SoundManager::unloadMenuSound()
{
    StopMusicStream(menuSound);
    UnloadMusicStream(menuSound);
    CloseAudioDevice();
}

void SoundManager::updateMenuSound()
{
    UpdateMusicStream(menuSound);
}

float SoundManager::getVolume() const
{
    return current_volume;
}

void SoundManager::setMusicVolume(float volume)
{
    current_volume = volume;
    SetMusicVolume(menuSound, volume);
}