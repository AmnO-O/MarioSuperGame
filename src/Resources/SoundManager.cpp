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

    brickSound = LoadSound("assets/sounds/block.wav");
    SetSoundVolume(brickSound, getEffectVolume());

    coinSound = LoadSound("assets/sounds/coin.wav");
    SetSoundVolume(coinSound, getEffectVolume());

    mushroomSound = LoadSound("assets/sounds/mushroom.wav");
    SetSoundVolume(mushroomSound, getEffectVolume());

    powerUpSound = LoadSound("assets/sounds/powerUpAppear.wav");
    SetSoundVolume(powerUpSound, getEffectVolume() * 2.5f);

    fireballSound = LoadSound("assets/sounds/fireball.wav");
    SetSoundVolume(fireballSound, getEffectVolume());

    pipedownSound = LoadSound("assets/sounds/pipedown.wav");
    SetSoundVolume(pipedownSound, getEffectVolume());

    flagpoleSound = LoadSound("assets/sounds/flagpole.wav");
    SetSoundVolume(flagpoleSound, getEffectVolume());

    stompSound = LoadSound("assets/sounds/stomp.wav");
    SetSoundVolume(stompSound, getEffectVolume());

    warningSound = LoadSound("assets/sounds/warning.wav");
    SetSoundVolume(warningSound, getEffectVolume());
}

void SoundManager::unloadAll() 
{
    UnloadMusicStream(playMusic);
    UnloadSound(deathSound);
    UnloadSound(gameOverSound);
    UnloadSound(jumpSound);
    UnloadSound(brickSound);
    UnloadSound(coinSound);
    UnloadSound(mushroomSound);
    UnloadSound(powerUpSound);
    UnloadSound(fireballSound);
    UnloadSound(pipedownSound);
    UnloadSound(flagpoleSound);
    UnloadSound(stompSound);
    UnloadSound(warningSound);
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
    SetSoundVolume(brickSound, volume);
    SetSoundVolume(coinSound, volume);
    SetSoundVolume(mushroomSound, volume);
    SetSoundVolume(powerUpSound, volume);
    SetSoundVolume(fireballSound, volume);
    SetSoundVolume(pipedownSound, volume);
    SetSoundVolume(flagpoleSound, volume);
    SetSoundVolume(stompSound, volume);
    SetSoundVolume(warningSound, volume);
}