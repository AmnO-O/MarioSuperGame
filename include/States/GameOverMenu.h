#ifndef GAME_OVER_H
#define GAME_OVER_H

#include <raylib.h>
#include <string>
#include <memory>
#include "Resources/StateManager.h"
#include "Resources/SoundManager.h"
#include "Widgets/Button.h"


class GameOverMenu: public GameState
{
    private:

    Font font;
    NormalButton restart_button;
    NormalButton exit_button;
    std::string title;
    int prevMapIndex;
    bool isprevMario;

    public:

        GameOverMenu(int mapIndex, bool checkMario);
        ~GameOverMenu() = default;

        void drawStats(); 
        void processInput() override {};
        void update(float deltaTime) override;
        void render() override;
};

#endif