#include "VolumeSlider.h"

VolumeSlider::VolumeSlider(float x, float y, float width, float height, SoundManager& soundManager)
    : slider({x, y, width, height}),
      volume(soundManager.getVolume()),
      backgroundColor(LIGHTGRAY),
      fillColor(GREEN),
      knobColor(RED), 
      soundManager(soundManager) 
{

}

void VolumeSlider::update() {
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();
        if (CheckCollisionPointRec(mousePos, slider)) {
            volume = (mousePos.x - slider.x) / slider.width; // Calculate volume (0.0 to 1.0)
            volume = Clamp(volume, 0.0f, 1.0f); // Ensure volume stays within bounds
            soundManager.setMusicVolume(volume);
        }
    }
}

void VolumeSlider::render(Font font) {
    // Draw slider background
    DrawRectangleRec(slider, backgroundColor);

    // Draw filled portion of the slider
    DrawRectangle(slider.x, slider.y, slider.width * volume, slider.height, fillColor);

    // Draw circular knob
    float knobX = slider.x + slider.width * volume; // Position of the knob
    float knobY = slider.y + slider.height / 2;     // Centered vertically
    DrawCircle(knobX, knobY, slider.height / 2, knobColor);

    // Render volume text
    std::string volumeText = std::to_string(static_cast<int>(volume * 100)) + "%";
    DrawTextEx(font, volumeText.c_str(), {slider.x + slider.width + 10, slider.y}, 20, 2, BLACK);
}

float VolumeSlider::getCurrentVolume() const {
    return volume;
}

void VolumeSlider::setCurrentVolume(float newVolume)
{
    volume = Clamp(newVolume, 0.0f, 1.0f);
}