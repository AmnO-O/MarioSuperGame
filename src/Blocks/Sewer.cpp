#include "Blocks/Sewer.h"
#include "Resources/SoundManager.h"

Sewer::Sewer(Texture2D &tex, std::istream &is) : Block(tex) {
    is >> head.x >> head.y >> head.width >> head.height;
    is >> body.x >> body.y >> body.width >> body.height;
    is >> pos.x >> pos.y;
    is >> height;
    is >> canDown;
    if (canDown) {
        is >> tp.x >> tp.y;
        is >> cam.x >> cam.y;
    }
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

void Sewer::Update(float deltaTime, Player* player) { 
    if (!canDown) return;
    if (hasDowned){
        if(animationEnterSewer.doneAction()){
            hasDowned = false;
            animationEnterSewer.resetAll(); 
        }
        animationEnterSewer.update(deltaTime); 
    }


    if (player) {
        Rectangle body = player->getHitbox(); 
        Rectangle hitbox = getHitbox();
        // Check overlap
        float left = (body.x + body.width) - hitbox.x;
        float right = (hitbox.x + hitbox.width) - body.x;
        float top = (body.y + body.height) - hitbox.y;
        float bottom = (hitbox.y + hitbox.height) - body.y;
        //if (left <= 0 || right <= 0 || top <= 0 || bottom <= 0) return;

        // Find minimal penetration
        float minPen = left;
        enum Dir { LEFT, RIGHT, TOP, BOTTOM } dir = LEFT;
        if (right < minPen) { minPen = right; dir = RIGHT; }
        if (top < minPen) { minPen = top; dir = TOP; }
        if (bottom < minPen) { minPen = bottom; dir = BOTTOM; }

        if (dir == TOP && body.y + body.height >= hitbox.y - 0.2) { // Player hit Question from below
            if( hitbox.x + 2 < body.x  && body.x + body.width < hitbox.x + hitbox.width - 2){
                if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)){
                    hasDowned = true;
                    PlaySound(SoundManager::getInstance().pipedownSound);
                    animationEnterSewer.setPlayer(player); 
                    animationEnterSewer.addAction(std::make_unique<EnterAction>());
                }
            }
        }
    }
}

Vector2 Sewer::changeCam() {
    if (hasDowned && animationEnterSewer.doneAction())
        return cam;
    return {-1.0f, -1.0f};
}
Vector2 Sewer::changePlayerPos() {
    if (hasDowned && animationEnterSewer.doneAction())
        return tp;
    return {-1.0f, -1.0f};
}
