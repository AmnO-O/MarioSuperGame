#include "Blocks/Brick.h"
#include "Character/Character.h"

Brick::Brick(Texture2D tex, std::istream &is) : Block(tex) {
    is >> srcRect.x >> srcRect.y >> srcRect.width >> srcRect.height;
    is >> fragmentRect.x >> fragmentRect.y >> fragmentRect.width >> fragmentRect.height;
    is >> pos.x >> pos.y;

    float fw = fragmentRect.width;
    float fh = fragmentRect.height;
    float sw = srcRect.width;
    float sh = srcRect.height;

    fragmentPos = {
        {pos.x - fw / 2, pos.y - fh / 2},
        {pos.x + sw - fw / 2, pos.y - fh / 2},
        {pos.x - fw / 2, pos.y + sh - fh / 2},
        {pos.x + sw - fw / 2, pos.y + sh - fh / 2}
    };
}

Rectangle Brick::getHitbox() const {
    if (stat == BlockStat::Broken || stat == BlockStat::Breaking) return {-1, -1, 0, 0};
    return { pos.x, pos.y - bounceOffset, srcRect.width, srcRect.height };
}

void Brick::Update(float delta) {
    if (stat == BlockStat::Broken) return; // Don't update if broken

    if (stat == BlockStat::Bouncing) {
        frameTime += delta;
        if (frameTime <= bounceTime / 2)
            bounceOffset = (frameTime / (bounceTime / 2)) * bounceHeight;
        else
            if (frameTime < bounceTime)
                bounceOffset = ((bounceTime - frameTime) / (bounceTime / 2)) * bounceHeight;
            else {
                stat = BlockStat::Normal;
                bounceOffset = 0;
            }
        return;
    }

    if (stat == BlockStat::Breaking) {
        frameTime += delta;
        if (frameTime > rotateTime * 2)
            frameTime -= rotateTime * 2;
        for (int i = 0; i < 4; i++) {
            if (i % 2 == 0)
                fragmentPos[i].x -= fragmentVelocity.x * delta;
            else
                fragmentPos[i].x += fragmentVelocity.x * delta;
            fragmentPos[i].y += fragmentVelocity.y * delta;
        }
        fragmentVelocity.y += gravity * delta;
        if (fragmentPos[0].y > GetScreenHeight()) {
            stat = BlockStat::Broken;
            drawStat = DrawStat::None;
        }
        return;
    }
}

void Brick::Draw(DrawStat ds) const {
    if (drawStat != ds) return;

    if (stat == BlockStat::Broken) return; // Don't draw if broken

    if (stat == BlockStat::Breaking) {
        DrawFragment();
        return;
    }

    Rectangle dest = {
        pos.x,
        pos.y - bounceOffset,
        srcRect.width,
        srcRect.height
    };
    DrawTexturePro(tex, srcRect, dest, {0, 0}, 0.0f, WHITE);
}

void Brick::DrawFragment() const {

    for (int i = 0; i < 4; i++) {
        if (frameTime < rotateTime) {
            Rectangle dest = {
                fragmentPos[i].x,
                fragmentPos[i].y,
                fragmentRect.width,
                fragmentRect.height
            };
            DrawTexturePro(tex, fragmentRect, dest, {0, 0}, 0.0f, WHITE);
        }
        else {
            Rectangle dest = {
                fragmentPos[i].x + fragmentRect.width,
                fragmentPos[i].y,
                fragmentRect.width,
                fragmentRect.height
            };
            DrawTexturePro(tex, fragmentRect, dest, {0, 0}, 90.0f, WHITE);
        }
    }
}

void Brick::adaptCollision(ICollidable* other) {
    if (stat == BlockStat::Normal) {
        Character* Char = dynamic_cast<Character*>(other);
        if (Char) {
            Rectangle body = Char->getHitbox(); // Use character's hitbox
            Rectangle hitbox = getHitbox();
            // Check overlap
            float left = (body.x + body.width) - hitbox.x;
            float right = (hitbox.x + hitbox.width) - body.x;
            float top = (body.y + body.height) - hitbox.y;
            float bottom = (hitbox.y + hitbox.height) - body.y;
            if (left <= 0 || right <= 0 || top <= 0 || bottom <= 0) return;

            // Find minimal penetration
            float minPen = left;
            enum Dir { LEFT, RIGHT, TOP, BOTTOM } dir = LEFT;
            if (right < minPen) { minPen = right; dir = RIGHT; }
            if (top < minPen) { minPen = top; dir = TOP; }
            if (bottom < minPen) { minPen = bottom; dir = BOTTOM; }

            if (dir == BOTTOM) { // Player hit brick from below
                if (Char->isBig()) {
                    Break();
                } else {
                    Bounce();
                }
            }
        }
    }
}

void Brick::Break() {
    stat = BlockStat::Breaking;
    drawStat = DrawStat::Second;
    fragmentVelocity = initVelocity;
    frameTime = 0.0f;
}

void Brick::Bounce() {    
    stat = BlockStat::Bouncing;
    frameTime = 0.0f;
}

bool Brick::IsActive() const {
    return (stat != BlockStat::Broken && stat != BlockStat::Breaking);
}