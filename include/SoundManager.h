#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <raylib.h>
#include <string>

class SoundManager
{
    public:

    void loadMenuSound();
    void playMenuSound();
    void stopMenuSound();
    void updateMenuSound();
    
    /*void loadGameSound();
    void playGameSound();
    void stopGameSound();

    void loadEffect();
    void playEffect();
    void stopEffect();

    void muteAll();*/

    private:

        float volume = 1.0f; //Default volume
        const std::string menu_filePath = "D:/MarioSuperGame/assets/sounds/SuperMarioBros_theme_song.mp3";
        Music menuSound;
};

#endif