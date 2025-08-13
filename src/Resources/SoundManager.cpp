#include "Resources/SoundManager.h"

SoundManager& SoundManager::getInstance()
{
    static SoundManager instance;
    return instance;
}

void SoundManager::loadAll() 
{
	playMusic = LoadMusicStream("assets/sounds/SuperMarioBros_theme_song.mp3");
    SetMusicVolume(playMusic, getMusicVolume() * 0.5f);

    finalscoreSound = LoadSound("assets/sounds/finalcalc.wav");
    SetSoundVolume(finalscoreSound, getEffectVolume() * 0.5f);

    endSound = LoadSound("assets/sounds/end.wav");
    SetSoundVolume(endSound, getEffectVolume() * 0.5f);
	
	deathSound = LoadSound("assets/sounds/death.wav");
	SetSoundVolume(deathSound, getEffectVolume() * 0.5f);

    gameOverSound = LoadSound("assets/sounds/gameOver.wav");
	SetSoundVolume(gameOverSound, getEffectVolume() * 0.5f);

    jumpSound = LoadSound("assets/sounds/jump.wav");
	SetSoundVolume(jumpSound, getEffectVolume() * 0.5f);

    brickSound = LoadSound("assets/sounds/block.wav");
    SetSoundVolume(brickSound, getEffectVolume() * 0.5f);

    coinSound = LoadSound("assets/sounds/coin.wav");
    SetSoundVolume(coinSound, getEffectVolume() * 0.5f);

    mushroomSound = LoadSound("assets/sounds/mushroom.wav");
    SetSoundVolume(mushroomSound, getEffectVolume() * 0.5f);

    powerUpSound = LoadSound("assets/sounds/powerUpAppear.wav");
    SetSoundVolume(powerUpSound, getEffectVolume() * 1.5f);

    fireballSound = LoadSound("assets/sounds/fireball.wav");
    SetSoundVolume(fireballSound, getEffectVolume() * 0.5f);

    pipedownSound = LoadSound("assets/sounds/pipedown.wav");
    SetSoundVolume(pipedownSound, getEffectVolume() * 0.5f);

    flagpoleSound = LoadSound("assets/sounds/flagpole.wav");
    SetSoundVolume(flagpoleSound, getEffectVolume() * 0.5f);

    stompSound = LoadSound("assets/sounds/stomp.wav");
    SetSoundVolume(stompSound, getEffectVolume() * 0.5f);

    warningSound = LoadSound("assets/sounds/warning.wav");
    SetSoundVolume(warningSound, getEffectVolume() * 0.5f);
}

void SoundManager::unloadAll() 
{
    UnloadMusicStream(playMusic);
    UnloadSound(finalscoreSound);
    UnloadSound(endSound);
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
    SetSoundVolume(finalscoreSound, volume);
    SetSoundVolume(endSound, volume);
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