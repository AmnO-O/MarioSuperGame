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

        float current_volume = 1.0f; //Current volume = default volume when first init

    public:

        static SoundManager& getInstance();
        static std::unordered_map<std::string, Sound> effects;

        Music playMusic;
        Sound deathSound;
        Sound gameOverSound;

        bool death_played = false;
        bool game_over_played = false;

        static void loadAllSounds(const std::string& folderPath);
	    static void unloadAllSounds();

        float getVolume() const;
        void setMusicVolume(float volume);
   
};

#endif