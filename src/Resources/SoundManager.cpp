#include "Resources/SoundManager.h"

SoundManager& SoundManager::getInstance()
{
    static SoundManager instance;
    return instance;
}

void SoundManager::loadPlayMusic()
{
    playMusic = LoadMusicStream(music_path.c_str());
    SetMusicVolume(playMusic, current_volume);
}

void SoundManager::playPlayMusic()
{
    PlayMusicStream(playMusic);
}

void SoundManager::pausePlayMusic()
{
    PauseMusicStream(playMusic);
}

void SoundManager::resumePlayMusic()
{
    ResumeMusicStream(playMusic);
}

void SoundManager::stopPlayMusic()
{
    StopMusicStream(playMusic);
}

void SoundManager::unloadPlayMusic()
{
    UnloadMusicStream(playMusic);

}

void SoundManager::updatePlayMusic()
{
    UpdateMusicStream(playMusic);
}

void SoundManager::loadDeathSound()
{
    deathSound = LoadSound(death_path.c_str());
    SetSoundVolume(deathSound, current_volume);
}
void SoundManager::playDeathSound()
{
    PlaySound(deathSound);
}

void SoundManager::stopDeathSound()
{
    StopSound(deathSound);
}

void SoundManager::unloadDeathSound()
{
    UnloadSound(deathSound);
}

void SoundManager::loadGameOverSound()
{
    gameOverSound = LoadSound(gameOver_path.c_str());
    SetSoundVolume(gameOverSound, current_volume);
}

void SoundManager::playGameOverSound()
{
    PlaySound(gameOverSound);
}

void SoundManager::stopGameOverSound()
{
    StopSound(gameOverSound);
}

void SoundManager::unloadGameOverSound()
{
    UnloadSound(gameOverSound);
}

bool SoundManager::isPlayingDeathSound() const
{
    return IsSoundPlaying(deathSound);
}

float SoundManager::getVolume() const
{
    return current_volume;
}

void SoundManager::setMusicVolume(float volume)
{
    current_volume = volume;
    SetMusicVolume(playMusic, volume);
}