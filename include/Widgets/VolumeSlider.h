#ifndef VOLUME_SLIDER_H
#define VOLUME_SLIDER_H

#include <raylib.h>
#include <raymath.h>
#include <string>
#include "../Resources/SoundManager.h"

class VolumeSlider 
{
    private:
        Rectangle slider; 
        float volume;
        Color background_color; 
        Color fill_color;           
        Color knob_color;           
        bool isEffect;

    public:
        
        VolumeSlider(Rectangle frame, bool isEffectSlider);

        void update();
        void render(); 
};

#endif