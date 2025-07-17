#ifndef SUB_MENU_H
#define SUB_MENU_H

#include <raylib.h>
#include "Button.h"
#include "MenuState.h"
#include <memory>
#include <string>
#include <functional>

class SubMenu : public MenuState
{
    private:

        NormalButton new_game_button;
        NormalButton load_game_button;
        ImageButton return_button;
        Texture2D sub_background;
        std::string title;

        std::function<void(std::unique_ptr<MenuState>)> switchStateCallback;

    public:

        SubMenu(std::function<void(std::unique_ptr<MenuState>)> switchStateCallback, const std::string& title);

        void unload() override;
        void update(float deltaTime) override;
        void render() override;   
};

#endif 