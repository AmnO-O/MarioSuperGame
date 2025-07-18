#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <raylib.h>
#include "Button.h"
#include "MenuState.h"
#include "StateManager.h"
#include <memory>
#include <string>

class MainMenu : public MenuState
{
    private:

        NormalButton mario_button;
        NormalButton luigi_button;
        Texture2D background;
        StateManager& stateManager;

    public:

        MainMenu(StateManager& stateManager);

        void unload() override;
        void update(float deltaTime) override;
        void render() override;   
};

#endif 