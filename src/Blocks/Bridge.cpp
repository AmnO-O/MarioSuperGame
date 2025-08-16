#include "Blocks/Bridge.h"
#include "Resources/SoundManager.h"

Bridge::Bridge(Texture2D &tex, std::istream &is) : Block(tex), ani(tex, false, 0.2f) {    
    int n = 0;
    is >> n;
    for (int i = 0; i < n; i++) {
        int x, y, w, h;
        is >> x >> y >> w >> h;
        ani.addRect({1.0f * x, 1.0f * y, 1.0f * w, 1.0f * h});
    }
    is >> body.x >> body.y >> body.width >> body.height;
    is >> pos.x >> pos.y;
    is >> bodyPos.x >> bodyPos.y;
    is >> width;
    if (width < body.width)
        throw ResourceException("Bridge width < Bridge Body!");
    
}

Rectangle Bridge::getHitbox() const {   
    return {bodyPos.x, bodyPos.y, 1.0f * width, body.height};
}

void Bridge::Draw(DrawStat ds) const {
    if (drawStat != ds) return;
    if (stat == BlockStat::Normal)
        ani.Draw(pos);
    for (int i = 0; i < (int)width / (int)body.width; i++) {
        DrawTextureRec(tex, body, {bodyPos.x + body.width * i, bodyPos.y}, WHITE);
    }
    Rectangle rec = body;
    rec.width = width - body.width * ((int)width / (int)body.width);
    DrawTextureRec(tex, rec, {bodyPos.x + width - rec.width, bodyPos.y}, WHITE);
}

void Bridge::Update(float deltaTime, Player* player) { 
    if (hasBroken) hasBroken = false;

    if (stat == BlockStat::Breaking)
        width -= deltaTime * 104.0f;
    if (width <= 0.0f) {
        stat = BlockStat::Broken;
        width = 0.0f;
    }

    if (stat != BlockStat::Normal) return;
    ani.update(deltaTime);

    if (player) {
        Rectangle body = player->getHitbox(); 
        Vector2 shape = ani.getCurrentShape();
        Rectangle hitbox = {pos.x, pos.y, shape.x, shape.y};
        if (CheckCollisionRecs(body, hitbox)) {
            stat = BlockStat::Breaking;
            hasBroken = true;
        }
    }
}

void Bridge::changePlayerPos(PlayerActionManager &pm) {
    // if (hasBroken && animationEnterBridge.doneAction()) {
    if (hasBroken) {
    }
}

void Bridge::save(std::ostream &os) {
    os << (int)stat << " " << width << " " << hasBroken << "\n";
}
void Bridge::load(std::istream &is) {
    is >> stat >> width >> hasBroken;
}