#include "VolumeSlider.h"

VolumeSlider::VolumeSlider(Rectangle frame, SoundManager& soundManager)
    : slider(frame),
      volume(soundManager.getVolume()),
      background_color(LIGHTGRAY),
      fill_color(GREEN),
      knob_color(RED), 
      soundManager(soundManager) 
{

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
            soundManager.setMusicVolume(volume);
        }
    }
}

void VolumeSlider::render() 
{
    const float roundness = 0.5f;
    const int segments = 16;
    DrawRectangleRounded(slider, roundness, segments, background_color);

    Rectangle filled_slider = {slider.x, slider.y, slider.width * volume, slider.height};
    DrawRectangleRounded(filled_slider, roundness, segments, fill_color);

    float knobX = slider.x + slider.width * volume; 
    float knobY = slider.y + slider.height / 2;    
    DrawCircle(knobX, knobY, slider.height / 2, knob_color);
}

float VolumeSlider::getCurrentVolume() const 
{
    return volume;
}

void VolumeSlider::setCurrentVolume(float newVolume)
{
    volume = Clamp(newVolume, 0.0f, 1.0f);
}