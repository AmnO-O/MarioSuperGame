#ifndef SUB_MENU_H
#define SUB_MENU_H

#include <raylib.h>
#include "Button.h"
#include "MenuState.h"
#include "StateManager.h"
#include <memory>
#include <string>

class SubMenu : public MenuState
{
    private:

        NormalButton new_game_button;
        NormalButton load_game_button;
        ImageButton return_button;
        Texture2D sub_background;
        std::string title;  
        StateManager& stateManager;

    public:

        SubMenu(StateManager& stateManager, const std::string& title);
        void unload() override;
        void update(float deltaTime) override;
        void render() override;   
};

#endif 