#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <raylib.h>
#include "../Widgets/Button.h"
#include "../Resources/StateManager.h"
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

    public:

        MainMenu();
        ~MainMenu();
        
        void processInput() override {};
        void update(float deltaTime) override;
        void render() override;   
};

#endif 