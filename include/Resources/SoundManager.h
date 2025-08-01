#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <raylib.h>
#include <string>


class SoundManager
{
    private:

        float current_volume = 1.0f; //Current volume = default volume when first init
        const std::string menu_filePath = "../assets/sounds/SuperMarioBros_theme_song.mp3";
        Music menuSound;
    
    public:

    void loadMenuSound();
    void playMenuSound();
    void stopMenuSound();
    void updateMenuSound();

    float getVolume() const;
    void setMusicVolume(float volume);
    
    /*void loadGameSound();
    void playGameSound();
    void stopGameSound();

    void loadEffect();
    void playEffect();
    void stopEffect();

    void muteAll();*/
};

#endif