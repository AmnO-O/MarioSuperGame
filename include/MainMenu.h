#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <raylib.h>
#include "Button.h"
#include "MenuState.h"
#include <memory>
#include <string>
#include <functional>

class MainMenu : public MenuState
{
    private:

        NormalButton mario_button;
        NormalButton luigi_button;
        Texture2D background;

    public:

        MainMenu(std::function<void(std::unique_ptr<MenuState>)> switchStateCallback);

        void unload() override;
        void update(float deltaTime) override;
        void render() override;   
};

#endif 