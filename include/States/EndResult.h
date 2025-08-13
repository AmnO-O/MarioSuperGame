#ifndef END_RESULT_H
#define END_RESULT_H

#include <raylib.h>
#include <string>
#include "Resources/StateManager.h"
#include "Resources/SoundManager.h"
#include "Resources/StatsManager.h"
#include "Widgets/Button.h"


class EndResult : public GameState
{
    private:

        Font font;
        std::string title;
        NormalButton back_button;
        int prevMapIndex;


    public:

        EndResult(int mIndex);
        ~EndResult() = default;

        void drawStats();
        void backToMainMenu();
        void processInput() override {};
        void update(float deltaTime) override;
        void render() override;    
};

#endif