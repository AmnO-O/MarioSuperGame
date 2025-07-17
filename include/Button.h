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

        ImageButton() = default; 
        ImageButton(const std::string& imagePath, Rectangle frame, std::function<void()> onClick);
        ~ImageButton();

        void update(float deltaTime);
        void render();


    private:

        std::string imagePath; 
        Texture2D image; 
        Rectangle frame;
        std::function<void()> onClick;
};

#endif BUTTON_H