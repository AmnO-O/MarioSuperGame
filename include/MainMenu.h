#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <raylib.h>
#include "Button.h"
#include "State.h"
#include <memory>
#include <string>

class MainMenu
{
    private:

        NormalButton one_player_button;
        NormalButton two_player_button;
        ImageButton settings_button;
        Texture2D background;

    public:

        MainMenu();

        void unload();
        void update(float deltaTime);
        void render();   
};

class SoundManager
{
    public:


};


#endif 