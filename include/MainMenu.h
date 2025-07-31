#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <raylib.h>
#include "Button.h"
#include "StateManager.h"
#include "SoundManager.h"
#include <memory>
#include <string>

class MainMenu : public MenuState
{
    private:

        NormalButton mario_button;
        NormalButton luigi_button;
        ImageButton settings_button;
        Texture2D settings_button_state;
        Texture2D background;
        StateManager& stateManager;
        SoundManager& soundManager;

    public:

        MainMenu(StateManager& stateManager, SoundManager& soundManager);
        ~MainMenu();

        void update(float deltaTime) override;
        void render() override;   
};

#endif 