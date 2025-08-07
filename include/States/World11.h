#ifndef WORLD_11_H
#define WORLD_11_H

#include "../Character/Character.h"
#include "../MyCamera2D.h"
#include <vector>
#include "../Resources/Map.h"
#include "../Observer/Observer.h"
#include "../Object/Creator.h"
#include "../Resources/StateManager.h"
#include "../Resources/SoundManager.h"
#include "../Widgets/Button.h"
#include <iostream>

class PopUpMenu1_1
{
    private:

        NormalButton resume_button;
        NormalButton restart_button;
        NormalButton exit_button;
        NormalButton save_button;
        Rectangle frame;

        StateManager& stateManager;
        SoundManager& soundManager;

    public:

        PopUpMenu1_1(StateManager& stateManager, SoundManager& soundManager);
        ~PopUpMenu1_1() = default;

        bool isVisible;
        void restart(StateManager& stateManager, SoundManager& soundManager);
        void exitGame(StateManager& stateManager, SoundManager& soundManager);
        void toggle();
        void update(float deltaTime);
        void render();
};


class World1_1: public GameState
{

    private:

        std::vector<Map> maps = {};
        int currentMap = 0;
        Player *character; 
        MyCamera2D *myCam; 
        
        ImageButton settings_button;
        Texture2D settings_button_state;
        PopUpMenu1_1 popup_menu;

        StateManager& stateManager;
        SoundManager& soundManager;

    public:

        World1_1(StateManager& stateManager, SoundManager& soundManager);
        ~World1_1();

        void processInput() override;
        void update(float deltaTime) override;
        void render() override;
        bool isRunning;
};



#endif