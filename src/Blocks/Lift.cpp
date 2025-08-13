#include "Blocks/Lift.h"
#include "Resources/SoundManager.h"

Lift::Lift(Texture2D &tex, std::istream &is) : Block(tex) {
    is >> srcRect.x >> srcRect.y >> srcRect.width >> srcRect.height;
    is >> width;
    is >> pos.x >> pos.y;
    is >> start.x >> start.y;
    is >> des.x >> des.y;
    is >> canBack;
    if (!canBack) {
        bool inverse;
        is >> inverse;
        if (inverse) {
            velocity.x *= -1;
            velocity.y *= -1;
        }
    }
    // if (width < srcRect.width)
    //     throw ResourceException("Lift width < Lift Rec!");
    
}

Rectangle Lift::getHitbox() const {   
    return {pos.x, pos.y, 1.0f * width, srcRect.height};
}

void Lift::Draw(DrawStat ds) const {
    if (drawStat != ds) return;
    for (int i = 0; i < (width) / (int)srcRect.width; i++) {
        DrawTextureRec(tex, srcRect, {pos.x + i * srcRect.width, pos.y}, WHITE);
    }
    Rectangle rec = srcRect;
    rec.width = width - srcRect.width * ((width) / (int)srcRect.width);
    DrawTextureRec(tex, rec, {pos.x + width - rec.width, pos.y}, WHITE);
}

void Lift::Update(float deltaTime, Player* player) { 
    Rectangle hitbox = getHitbox();
    if (canBack) {
        if (pos.x > des.x || pos.x < start.x)
            velocity.x *= -1;
        if (pos.y > des.y || pos.y < start.y)
            velocity.y *= -1; 
    } 
    Vector2 distance = {velocity.x * deltaTime, velocity.y * deltaTime};   
    pos.x += distance.x;
    pos.y += distance.y;
    if(!canBack) {
        if (pos.x > des.x)
            pos.x = start.x;
        if (pos.x < start.x)
            pos.x  = des.x;
        if (pos.y > des.y)
            pos.y = start.y;
        if (pos.y < start.y)
            pos.y  = des.y;
    }
    // std::cout << distance.x << " " << distance.y << '\n';
    if (player) {
        Rectangle body = player->getHitbox(); 
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

        if (dir == TOP) { 
            Vector2 playerPos = player->getPosition();
            playerPos.x += distance.x;
            playerPos.y += distance.y;
            player->setGroundLevel(playerPos.y);
            player->setPosition({playerPos.x, playerPos.y});
            player->setOnGround();
        }
    }
}