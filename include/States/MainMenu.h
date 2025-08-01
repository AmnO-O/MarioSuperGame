#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <raylib.h>
#include "../Widgets/Button.h"
#include "../Resources/StateManager.h"
#include "../Resources/SoundManager.h"
#include <memory>
#include <string>

class MainMenu : public GameState
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