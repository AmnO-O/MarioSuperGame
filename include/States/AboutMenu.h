#ifndef ABOUT_MENU_H
#define ABOUT_MENU_H

#include "../Resources/StateManager.h"
#include "raylib.h"
#include "../Widgets/Button.h"

class AboutMenu : public GameState
{
    private:
        
        Font font;
        Texture2D background;
        ImageButton return_button;
        Texture2D return_button_state;
        std::string info1 = "This is a Mario game project of the CS202 course, during the";
        std::string info2 = "2024-2025 semester of the Advanced Program in Computer"; 
        std::string info3 = "Science major. The game is designed using object-oriented";
        std::string info4 = "concepts in C++, along with the external library of Raylib"; 
        std::string info5 = "We hope that everyone would have a great time enjoying";
        std::string info6 = "the game. Any feedbacks will be highly appreciated :>";

        std::string con = "Contributors: ";
        std::string Nam = "Pham Huu Nam (24125015)";
        std::string Phong = "Nguyen Trong Hung Phong (24125073)";
        std::string Vi = "Le Quoc Vi (24125085)";
        std::string Vinh = "Bui Cong Vinh (24125086)";

    public:
        
        AboutMenu();
        ~AboutMenu();

        void processInput() override{}
        void update(float deltaTime) override;
        void render() override;
};

#endif