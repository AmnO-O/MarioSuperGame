#ifndef VOLUME_SLIDER_H
#define VOLUME_SLIDER_H

#include <raylib.h>
#include <raymath.h>
#include <string>
#include "SoundManager.h"

class VolumeSlider {
private:
    Rectangle slider; // Slider rectangle
    float volume;
    Color backgroundColor; // Background color of the slider
    Color fillColor;       // Fill color of the slider
    Color knobColor;       // Color of the circular knob
    SoundManager& soundManager;

public:
    VolumeSlider(float x, float y, float width, float height, SoundManager& soundManager);

    void update(); // Update slider based on mouse input
    void render(Font font); // Render slider and volume text
    float getCurrentVolume() const; // Get the current volume
    void setCurrentVolume(float newVolume);
};

#endif