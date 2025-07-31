#ifndef WORLD_11_H
#define WORLD_11_H

#include "Character/Character.h"
#include "Character/MyCamera2D.h"
#include <vector>
#include "Map.h"
#include "Observer/Observer.h"
#include "Character/IPowerUpCreator.h"
#include "StateManager.h"
#include "SoundManager.h"
#include <iostream>


class World1_1: public MenuState
{

    private:

        CollisionManager cm;
        std::vector<Map> maps = {};
        int currentMap = 0;
        Player *character; 
        MyCamera2D *myCam; 

        IPowerUpCreator *powerUpCreator; 
        PowerUp *item; 

    public:

        World1_1();
        ~World1_1();

        void update(float deltaTime) override;
        void render() override;
        bool isRunning;
};

#endif