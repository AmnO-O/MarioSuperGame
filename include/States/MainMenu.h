#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <raylib.h>
#include "../Widgets/Button.h"
#include "../Resources/StateManager.h"
#include <memory>
#include <string>
#include "AboutMenu.h"
class MainMenu : public GameState
{
    private:

        NormalButton new_game_button;
        NormalButton load_game_button;
        NormalButton about_button; 

        ImageButton settings_button;
        Texture2D settings_button_state;
        Texture2D background;

    public:

        MainMenu();
        ~MainMenu();
        
        void loadGame(const std::string& filename);
        void processInput() override {};
        void update(float deltaTime) override;
        void render() override;   
};

#endif 