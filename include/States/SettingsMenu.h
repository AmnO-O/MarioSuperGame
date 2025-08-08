#ifndef SETTINGS_MENU_H
#define SETTINGS_MENU_H

#include <raylib.h>
#include "../Widgets/Button.h"
#include "../Resources/StateManager.h"
#include "../Widgets/VolumeSlider.h"
#include <memory>
#include <string>

class SettingsMenu : public GameState
{
    private:

        Texture2D settings_background;
        ImageButton return_button;
        Texture2D return_button_state;
        std::string music;
        std::string soundFX;
        Font font; 
        VolumeSlider slider;

    public:

        SettingsMenu();
        ~SettingsMenu();
        
        void processInput() override {};
        void update(float deltaTime) override;
        void render() override;   
};

#endif 