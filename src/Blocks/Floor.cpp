#include "Blocks/Floor.h"

Floor::Floor(Texture2D &tex, std::istream &is) : Block(tex) {
    is >> srcRect.x >> srcRect.y >> srcRect.width >> srcRect.height;
    is >> pos.x >> pos.y;
    is >> num;
}

Rectangle Floor::getHitbox() const {   
    return {pos.x, pos.y, srcRect.width * num, srcRect.height};
}

void Floor::Draw(DrawStat ds) const {
    if (drawStat != ds) return;
    Rectangle desRect = {pos.x, pos.y, srcRect.width, srcRect.height};
    for (int i = 0; i < num; i++) {
        DrawTexturePro(this->tex, srcRect, desRect, {0, 0}, 0.0f, WHITE);
        desRect.x += srcRect.width;
    }
}

void Floor::Update(float delta, Player* player) {
    // if (drawStat == DrawStat::None) return;
    // Rectangle hitbox = getHitbox();
    // if ()
}

void Floor::save(std::ostream &os) {
    
}