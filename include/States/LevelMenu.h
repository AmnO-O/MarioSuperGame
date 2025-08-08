#ifndef LEVEL_MENU_H
#define LEVEL_MENU_H

#include <raylib.h>
#include "../Resources/StateManager.h"
#include "../Widgets/Button.h"
#include <string>
#include <vector>
#include <memory>

class LevelMenu : public GameState
{
    private:

        Texture2D level_background;
        ImageButton world1_1;
        ImageButton world1_2;
        ImageButton world1_3;
        ImageButton world1_4;
        ImageButton return_button;
        Texture2D return_button_state;

        std::string high_score;
        std::string title;
        Font font;
        bool isMario; 

    public: 

        LevelMenu(bool isMario);
        ~LevelMenu(); 

        void drawBorder(Rectangle bounds);
        void processInput() override {};
        void update(float deltaTime) override;
        void render() override;

};

#endif