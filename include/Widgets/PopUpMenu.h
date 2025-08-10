#ifndef POP_UP_MENU_H
#define POP_UP_MENU_H

#include <raylib.h>
#include <string>
#include <memory>
#include "Widgets/Button.h"

class PopUpMenu
{
    private:

        NormalButton resume_button;
        NormalButton restart_button;
        NormalButton exit_button;
        NormalButton save_button;
        Rectangle frame;


    public:

        PopUpMenu();
        ~PopUpMenu() = default;

        bool isVisible;
        bool isDeathMusicPlayed = false;
        bool isGOMPlayed = false;

        void restart();
        void exitGame();
        void toggle();
        void update(float deltaTime);
        void render();
};


#endif