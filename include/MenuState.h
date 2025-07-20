#ifndef MENU_STATE_H
#define MENU_STATE_H

class MenuState
{
    public:

        virtual ~MenuState() = default;

        virtual void update(float deltaTime) = 0;
        virtual void render() = 0;
};

#endif 