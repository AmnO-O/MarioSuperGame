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

    DrawRectangleRec(frame, Fade(currentColor, 0.25f));

    int fontSize = static_cast<int>(frame.height * 0.6f); 
    if (fontSize < 8) fontSize = 8;

    Vector2 textSize = MeasureTextEx(font, text.c_str(), (float)fontSize, 2.0f);
    Vector2 textPos;
    textPos.x = frame.x + (frame.width - textSize.x) / 2.0f;
    textPos.y = frame.y + (frame.height - textSize.y) / 2.0f;

    DrawTextEx(font, text.c_str(), textPos, (float)fontSize, 2.0f, currentColor);

    // Vector2 pos = GetMousePosition();
    // Color currentColor = CheckCollisionPointRec(pos, frame) ? hoverColor : normalColor;

    // DrawTextEx(font, text.c_str(), {frame.x, frame.y}, 50, 2, currentColor);
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
    DrawTexture(image, (int)frame.x, (int)frame.y, WHITE);
}