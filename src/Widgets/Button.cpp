#include "Widgets/Button.h"

NormalButton::NormalButton(const std::string& text, Rectangle rect, Color normalColor, Color hoverColor, std::function<void()> onClick)
    : text(text), frame(rect), normalColor(normalColor), hoverColor(hoverColor), onClick(onClick)
{
    font = LoadFont(fontPath.c_str());
}

NormalButton::~NormalButton()
{
    UnloadFont(font);
}

void NormalButton::update(float deltaTime)
{
    Vector2 pos = GetMousePosition();

    if (CheckCollisionPointRec(pos, frame))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            onClick(); 
    }
}

void NormalButton::render() 
{
    Vector2 pos = GetMousePosition();
    Color currentColor = CheckCollisionPointRec(pos, frame) ? hoverColor : normalColor;

    DrawTextEx(font, text.c_str(), {frame.x, frame.y}, 50, 2, currentColor);
}

ImageButton::ImageButton(const std::string& imagePath, Rectangle frame, std::function<void()> onClick)
    : imagePath(imagePath), frame(frame), onClick(onClick)
{
    image = LoadTexture(imagePath.c_str());
}

ImageButton::~ImageButton()
{
    UnloadTexture(image);
}

Rectangle ImageButton::getBounds() const
{
    return {frame.x - 7, frame.y - 7, frame.width + 14, frame.height + 14};
}

void ImageButton::update(float deltaTime)
{
    Vector2 pos = GetMousePosition();

    if (CheckCollisionPointRec(pos, frame) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        onClick();
}

void ImageButton::render()
{
    Vector2 pos = GetMousePosition();
    DrawTexture(image, frame.x, frame.y, WHITE);
}