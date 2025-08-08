#include "Resources/SoundManager.h"

SoundManager& SoundManager::getInstance()
{
    static SoundManager instance;
    return instance;
}

void SoundManager::loadAll() 
{
	playMusic = LoadMusicStream("assets/sounds/SuperMarioBros_theme_song.mp3");
    SetMusicVolume(playMusic, getMusicVolume());
	
	deathSound = LoadSound("assets/sounds/death.wav");
	SetSoundVolume(deathSound, getEffectVolume());

    gameOverSound = LoadSound("assets/sounds/gameOver.wav");
	SetSoundVolume(gameOverSound, getEffectVolume());

    jumpSound = LoadSound("assets/sounds/jump.wav");
	SetSoundVolume(jumpSound, getEffectVolume());
}

void SoundManager::unloadAll() 
{
    UnloadMusicStream(playMusic);
    UnloadSound(deathSound);
    UnloadSound(gameOverSound);
    UnloadSound(jumpSound);
}

float SoundManager::getMusicVolume() const
{
    return current_music_volume;
}

float SoundManager::getEffectVolume() const
{
    return current_effect_volume;
}

void SoundManager::setMusicVolume(float volume)
{
    current_music_volume = volume;
    SetMusicVolume(playMusic, volume);
}

void SoundManager::setEffectVolume(float volume)
{
    current_effect_volume = volume;
	SetSoundVolume(deathSound, volume);
	SetSoundVolume(gameOverSound, volume);
	SetSoundVolume(jumpSound, volume);
}