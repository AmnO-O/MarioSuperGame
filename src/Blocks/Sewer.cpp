#include "Blocks/Sewer.h"

Sewer::Sewer(Texture2D &tex, std::istream &is) : Block(tex) {
    is >> head.x >> head.y >> head.width >> head.height;
    is >> body.x >> body.y >> body.width >> body.height;
    is >> pos.x >> pos.y;
    is >> height;
    if (height < head.height)
        throw ResourceException("Sewer height < Sewer Head!");
}

Rectangle Sewer::getHitbox() const {   
    return {pos.x, pos.y, head.width, 1.0f * height};
}

void Sewer::Draw(DrawStat ds) const {
    if (drawStat != ds) return;
    DrawTextureRec(tex, head, pos, WHITE);
    for (int i = 0; i < ((int)height - (int)head.height) / (int)body.height; i++) {
        DrawTextureRec(tex, body, {pos.x, pos.y + head.height + body.height * i}, WHITE);
    }
    Rectangle rec = body;
    rec.height = height - head.height - body.height * (((int)height - (int)head.height) / (int)body.height);
    DrawTextureRec(tex, rec, {pos.x, pos.y + height - rec.height}, WHITE);
}

void Sewer::Update(float delta) {
    // if (drawStat == DrawStat::None) return;
    // Rectangle hitbox = getHitbox();
    // if ()
}