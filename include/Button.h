#ifndef BUTTON_H
#define BUTTON_H

#include <raylib.h>
#include <memory>
#include <string>
#include <functional>

class NormalButton
{
    private:

        std::string text;
        const std::string fontPath = "D:/MarioSuperGame/assets/fonts/SuperMarioBros.ttf";
        Font font;
        Rectangle frame;
        Color normalColor;
        Color hoverColor;
        std::function<void()> onClick;

    public:
        
        NormalButton() = default;
        NormalButton(const std::string& text, Rectangle rect, 
        Color normalColor, Color hoverColor, std::function<void()> onClick);
        ~NormalButton();

        void update(float deltaTime);
        void render();
};

class ImageButton
{
    private:

        std::string imagePath; 
        Texture2D image; 
        Rectangle frame;
        std::function<void()> onClick;
    
    public:

        ImageButton() = default; 
        ImageButton(const std::string& imagePath, Rectangle frame, std::function<void()> onClick);
        ~ImageButton();

        void update(float deltaTime);
        void render();
};

#endif BUTTON_H