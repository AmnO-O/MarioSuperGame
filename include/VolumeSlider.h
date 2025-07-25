#ifndef VOLUME_SLIDER_H
#define VOLUME_SLIDER_H

#include <raylib.h>
#include <raymath.h>
#include <string>
#include "SoundManager.h"

class VolumeSlider 
{
    private:
        Rectangle slider; 
        float volume;
        Color background_color; 
        Color fill_color;           
        Color knob_color;           
        SoundManager& soundManager;

    public:
        
        VolumeSlider(Rectangle frame, SoundManager& soundManager);

        void update();
        void render(); 
        float getCurrentVolume() const; 
        void setCurrentVolume(float newVolume);
};

#endif