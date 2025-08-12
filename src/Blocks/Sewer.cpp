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
        // if(animationEnterSewer.doneAction()){
            hasDowned = false;
            canDown = false;
        //     animationEnterSewer.resetAll(); 
        // }
        // animationEnterSewer.update(deltaTime); 
        return;
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

        if (dir == TOP && body.y + body.height >= hitbox.y - 0.2) { 
            if( hitbox.x + 4 < body.x  && body.x + body.width < hitbox.x + hitbox.width - 4){
                if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)){
                    hasDowned = true;
                    // animationEnterSewer.setPlayer(player); 
                    // animationEnterSewer.addAction(std::make_unique<TopEnterAction>());
                    PlaySound(SoundManager::getInstance().pipedownSound);
                    // animationEnterSewer.setPlayer(player); 
                    // animationEnterSewer.addAction(std::make_unique<TopEnterAction>());
                }
            }
        }
    }
}

void Sewer::changeCam(std::queue<Vector3> &camChange) {
    // if (hasDowned && animationEnterSewer.doneAction())
    //     return cam;
    // return {-1.0f, -1.0f};
    if (hasDowned)
        camChange.push({cam.x, cam.y, 2.0f});
}
void Sewer::changePlayerPos(PlayerActionManager &pm) {
    // if (hasDowned && animationEnterSewer.doneAction()) {
    if (hasDowned) {
        pm.addAction(std::make_unique<TopEnterAction>());
        pm.addAction(std::make_unique<SetPositionAction>(tp, true, 0.0f));
        // return tp;
    }
    // return {-1.0f, -1.0f};
}

Rectangle HorizontalSewer::getHitbox() const {
    return {pos.x, pos.y, 1.0f * height, head.height};
}

void HorizontalSewer::Draw(DrawStat ds) const {
    if (drawStat != ds) return;
    DrawTextureRec(tex, head, pos, WHITE);
    for (int i = 0; i < ((int)height - (int)head.height) / (int)body.height; i++) {
        DrawTextureRec(tex, body, {pos.x + head.width + body.width * i, pos.y}, WHITE);
    }
    Rectangle rec = body;
    rec.width = height - head.width - body.width * (((int)height - (int)head.width) / (int)body.width);
    DrawTextureRec(tex, rec, {pos.x + height - rec.width, pos.y}, WHITE);
}

void HorizontalSewer::Update(float deltaTime, Player* player) {
    if (!canDown) return;
    if (hasDowned){
        // if(animationEnterSewer.doneAction()){
            hasDowned = false;
            canDown = false;
        //     animationEnterSewer.resetAll(); 
        // }
        // animationEnterSewer.update(deltaTime); 
        return;
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

        if (dir == LEFT && body.x + body.width >= hitbox.x - 0.2) { 
            if( hitbox.y <= body.y  && body.y + body.height <= hitbox.y + hitbox.height){
                if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)){
                    hasDowned = true;
                    // animationEnterSewer.setPlayer(player); 
                    // animationEnterSewer.addAction(std::make_unique<HorizontalEnterAction>());
                    PlaySound(SoundManager::getInstance().pipedownSound);
                }
            }
        }
    }
}

void HorizontalSewer::changeCam(std::queue<Vector3> &camChange) {
    if (hasDowned) {
        camChange.push({cam.x, cam.y, 1.5f});
    }
}

void HorizontalSewer::changePlayerPos(PlayerActionManager &pm) {
    if (hasDowned) {
    // if (hasDowned && animationEnterSewer.doneAction()) {
        pm.addAction(std::make_unique<HorizontalEnterAction>());
        pm.addAction(std::make_unique<SetPositionAction>(tp, true, 0.0f));
        if (isDown)
            pm.addAction(std::make_unique<PopupAction>());
        // return tp;
    }
    // return {-1.0f, -1.0f};
}