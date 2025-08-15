#include "Widgets/VolumeSlider.h"

VolumeSlider::VolumeSlider(Rectangle frame, bool isEffectSlider)
    : slider(frame),
      isEffect(isEffectSlider),
      background_color(LIGHTGRAY),
      fill_color(GREEN),
      knob_color(RED) 
{
    if (isEffect)
        volume = SoundManager::getInstance().getEffectVolume();
    else
        volume = SoundManager::getInstance().getMusicVolume();
}

void VolumeSlider::update() 
{
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) 
    {
        Vector2 mousePos = GetMousePosition();
        if (CheckCollisionPointRec(mousePos, slider)) 
        {
            volume = (mousePos.x - slider.x) / slider.width; 
            volume = Clamp(volume, 0.0f, 1.0f);

            if (isEffect)
                SoundManager::getInstance().setEffectVolume(volume);
            else
                SoundManager::getInstance().setMusicVolume(volume);
        }
    }
}

void VolumeSlider::render() 
{
    const float roundness = 0.5f;
    const int segments = 16;
    DrawRectangleRounded(slider, roundness, segments, background_color);

    float fillWidth = volume * slider.width;

    Rectangle filled_slider = {slider.x, slider.y, fillWidth, slider.height};
    DrawRectangleRounded(filled_slider, roundness, segments, fill_color);

    float knobX = slider.x + volume * slider.width;
    float knobY = slider.y + slider.height / 2;    
    DrawCircle((int)knobX, (int)knobY, slider.height / 2, knob_color);
}

