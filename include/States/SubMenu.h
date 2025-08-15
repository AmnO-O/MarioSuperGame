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

        NormalButton mario_button;
        NormalButton luigi_button;
        NormalButton select_button; 

        ImageButton return_button;
        Texture2D return_button_state;
        Texture2D sub_background;
        std::string title; 
        Font titleFont; 

        std::vector<Texture2D> playerTextures;
        std::vector<Rectangle> playerPreviews;
        int selectedPlayer = 0; 
        int curHovered = 0; 
    public:

        SubMenu();
        ~SubMenu();

        void processInput() override {};
        void update(float deltaTime) override;
        void render() override;   
};

#endif 