#ifndef SETTINGS_MENU_H
#define SETTINGS_MENU_H

#include <raylib.h>
#include "Button.h"
#include "MenuState.h"
#include "StateManager.h"
#include "SoundManager.h"
#include "VolumeSlider.h"
#include <memory>
#include <string>

class SettingsMenu : public MenuState
{
    private:

        Texture2D settings_background;
        ImageButton return_button;
        Texture2D return_button_state;
        std::string music;
        std::string soundFX;
        Font font; 
        StateManager& stateManager;
        SoundManager& soundManager;
        VolumeSlider slider;

    public:

        SettingsMenu(StateManager& stateManager, SoundManager& soundManager);
        ~SettingsMenu();

        void update(float deltaTime) override;
        void render() override;   
};

#endif 