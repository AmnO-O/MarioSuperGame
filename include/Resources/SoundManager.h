#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <raylib.h>
#include <string>


class SoundManager
{
    private:

        SoundManager() = default; 
        SoundManager(const SoundManager&) = delete;
        SoundManager& operator=(const SoundManager&) = delete;

        float current_volume = 1.0f; //Current volume = default volume when first init
        const std::string music_path = "assets/sounds/SuperMarioBros_theme_song.mp3";
        const std::string death_path = "assets/sounds/death.wav";
        const std::string gameOver_path = "assets/sounds/gameOver.wav";

    public:

        static SoundManager& getInstance();

        Music playMusic;
        Sound deathSound;
        Sound gameOverSound;

        bool death_played = false;
        bool game_over_played = false;

        void loadPlayMusic();
        void playPlayMusic();
        void pausePlayMusic();
        void resumePlayMusic();
        void stopPlayMusic();
        void unloadPlayMusic();
        void updatePlayMusic();

        void loadDeathSound();
        void playDeathSound();
        void stopDeathSound();
        void unloadDeathSound();
        
        void loadGameOverSound();
        void playGameOverSound();
        void stopGameOverSound();
        void unloadGameOverSound();

        bool isPlayingDeathSound() const;

        float getVolume() const;
        void setMusicVolume(float volume);
   
};

#endif