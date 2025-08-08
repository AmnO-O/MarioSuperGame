#ifndef SUB_MENU_H
#define SUB_MENU_H

#include <raylib.h>
#include "../Widgets/Button.h"
#include "../Resources/StateManager.h"
#include <memory>
#include <string>

class SubMenu : public GameState
{
    private:

        NormalButton new_game_button;
        NormalButton load_game_button;
        ImageButton return_button;
        Texture2D return_button_state;
        Texture2D sub_background;
        std::string title; 
        Font titleFont; 
        bool isMario;

    public:

        SubMenu(bool isMario);
        ~SubMenu();

        void processInput() override {};
        void update(float deltaTime) override;
        void render() override;   
};

#endif 