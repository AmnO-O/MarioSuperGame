#include "Button.h"

NormalButton::NormalButton(const std::string& text, Rectangle rect, Color normalColor, Color hoverColor, std::function<void()> onClick)
    : text(text), frame(rect), normalColor(normalColor), hoverColor(hoverColor), onClick(onClick) {}

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

    DrawText(text.c_str(), frame.x, frame.y, 50, currentColor);
}