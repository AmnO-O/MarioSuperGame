#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <raylib.h>
#include <string>
#include <unordered_map>
#include <filesystem>


class SoundManager
{
    private:

        SoundManager() = default; 
        SoundManager(const SoundManager&) = delete;
        SoundManager& operator=(const SoundManager&) = delete;

        float current_music_volume = 0.5f; 
        float current_effect_volume = 0.5f;

    public:

        static SoundManager& getInstance();
        
        // Music
        Music playMusic;
        Sound deathSound;
        Sound gameOverSound;
        
        // Effects
        Sound jumpSound;
        Sound brickSound;
        Sound coinSound;
        Sound mushroomSound;
        Sound powerUpSound;
        Sound fireballSound;
        Sound pipedownSound;
        Sound flagpoleSound;
        
        bool death_played = false;
        bool game_over_played = false;

        void loadAll();
	    void unloadAll();

        float getMusicVolume() const;
        float getEffectVolume() const;
        void setMusicVolume(float volume);
        void setEffectVolume(float volume);

   
};

#endif