#include "Blocks/Fire.h"
#include <math.h>

Fire::Fire(Texture2D &tex, std::istream &is) : Block(tex) {
    is >> srcRect.x >> srcRect.y >> srcRect.width >> srcRect.height;
    is >> center.x >> center.y;
    is >> pos.x >> pos.y;
    is >> right;
    if (pos.x == center.x - srcRect.width / 2) {
        if (pos.y >= center.y - srcRect.height / 2)
            angle = 90.0f;
        else
            angle = 270.0f;
    }
    else {
        if (pos.x >= center.x - srcRect.width / 2)
            angle = 0.0f;
        else
            angle = 180.0f;
    }
}
    
Rectangle Fire::getHitbox() const {
    return {pos.x, pos.y, srcRect.width, srcRect.height};
}

void Fire::Draw(DrawStat ds) const {
    float degree = frametime / spinPeriod;
    DrawTexturePro(tex, srcRect, {pos.x + srcRect.width / 2, pos.y + srcRect.height / 2, srcRect.width, srcRect.height}, 
                    {srcRect.width / 2, srcRect.height / 2}, degree * 360, WHITE );
}

void Fire::Update(float delta, Player* player) {
    frametime += delta;
    if (frametime > spinPeriod)
        frametime -= spinPeriod;

    if (right)
        angle += delta / rotatePeriod * 360.0f;
    else
        angle -= delta / rotatePeriod * 360.0f;

    if (angle > 360.0f)
        angle -= 360.0f;
    if (angle < 0.0f)
        angle += 360.0f;

    // compute new position
    float rad = angle * DEG2RAD;
    float radius = sqrt((pos.x + srcRect.width / 2 - center.x) * (pos.x + srcRect.width / 2 - center.x)
                        + (pos.y + srcRect.height / 2 - center.y) * (pos.y + srcRect.height / 2 - center.y));
    pos.x = center.x + radius * cosf(rad) - srcRect.width / 2;
    pos.y = center.y + radius * sinf(rad) - srcRect.height / 2;
}

void Fire::save(std::ostream &os) {
    os << pos.x << " " << pos.y << " " << frametime << "\n";
}

void Fire::load(std::istream &is) {
    is >> pos.x >> pos.y >> frametime;
}