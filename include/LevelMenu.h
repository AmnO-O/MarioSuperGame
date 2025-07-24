#ifndef LEVEL_MENU_H
#define LEVEL_MENU_H

#include <raylib.h>
#include "MenuState.h"
#include "SoundManager.h"
#include "StateManager.h"
#include "Button.h"
#include <string>
#include <vector>
#include <memory>

class LevelMenu : public MenuState
{
    private:

        Texture2D level_background;
        //ImageButton world1_1;
        //ImageButton world1_2;
        //ImageButton world1_3;
        //ImageButton world1_4;
        ImageButton return_button;

        std::string high_score;
        std::string title;
        Font font;
        StateManager& stateManager;
        SoundManager& soundManager;
        bool isMario; 

    public: 

        LevelMenu(StateManager& stateManager, SoundManager& soundManager, bool isMario);
        ~LevelMenu(); 

        void update(float deltaTime) override;
        void render() override;

};

#endif