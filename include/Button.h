#ifndef BUTTON_H
#define BUTTON_H

#include <raylib.h>
#include <memory>
#include <string>
#include <functional>

class NormalButton
{
    public:
        
        NormalButton() = default;
        NormalButton(const std::string& text, Rectangle rect, 
        Color normalColor, Color hoverColor, std::function<void()> onClick);

        void update(float deltaTime);
        void render();

    private:

        std::string text;
        Rectangle frame;
        Color normalColor;
        Color hoverColor;
        std::function<void()> onClick;

};

class ImageButton
{
    public:


};

#endif BUTTON_H