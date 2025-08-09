#ifndef WORLD_H
#define WORLD_H

#include "../Character/Character.h"
#include "../MyCamera2D.h"
#include <vector>
#include "../Resources/Map.h"
#include "../Observer/Observer.h"
#include "../Object/Creator.h"
#include "../Resources/StateManager.h"
#include "../Resources/StatsManager.h"
#include "../Widgets/Button.h"
#include "../Widgets/PopUpMenu.h"
#include "../Resources/Timer.h"
#include <iostream>

class World: public GameState
{

    private:

        Map* currentMap;
        int mapIndex;
        Font font;
        Player *character; 
        
        ImageButton settings_button;
        Texture2D settings_button_state;
        Texture2D coin_display;
        PopUpMenu popup_menu;
        
        bool startdeath = false;
        bool GOMshown = false;
        bool GOMplayed = false;
        
        bool isMario;


    public:

        int score_number;
        int number_of_coins;
        float remaining_time;
        
        World(bool checkMario, int index);
        ~World();

        bool getIsMario() const;
        int getMapIndex() const;

        void drawStats();
        void processInput() override;
        void update(float deltaTime) override;
        void render() override;

       
        bool isRunning;
};



#endif