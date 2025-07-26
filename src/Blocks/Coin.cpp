#include "Blocks/Coin.h"
#include "Character/Character.h"

Coin::Coin(Texture2D tex, std::istream &is) : Block(tex), ani(tex, false) {
    int num = 0;
    is >> num;
    for (int i = 0; i < num; i++) {
        int x, y, w, h;
        is >> x >> y >> w >> h;
        ani.addRect({1.0f * x, 1.0f * y, 1.0f * w, 1.0f * h});
    }
    is >> pos.x >> pos.y;
    coinAni.input(tex, is, getHitbox());
}

Rectangle Coin::getHitbox() const {
    if (!IsActive()) return {-1, -1, 0, 0};
    Vector2 srcRect = ani.getCurrentShape();
    return { pos.x, pos.y, srcRect.x, srcRect.y };
}

void Coin::Update(float delta) {
    if (stat == BlockStat::Broken) return; // Don't update if broken
    if (stat == BlockStat::Bouncing) {
        coinAni.Update(delta);
        if (coinAni.ended()) {
            stat = BlockStat::Broken;
            drawStat = DrawStat::None;
        }
        return;
    }
    if (stat == BlockStat::Normal)
        ani.update(delta);
}

void Coin::Draw(DrawStat ds) const {
    if (drawStat != ds) return;

    if (stat == BlockStat::Broken || stat == BlockStat::Breaking) return; // Don't draw if broken

    if (stat == BlockStat::Normal)
        ani.Draw(pos);
    else
        coinAni.Draw();
}


void Coin::adaptCollision(ICollidable* other) {
    if (stat == BlockStat::Normal) {
        if (dynamic_cast<Character*>(other)) {
            Break();
        }
        else {
            Block* b = dynamic_cast<Block*>(other);
            if (b) {            
                Rectangle body = b->getHitbox(); // Use character's hitbox
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
                    Bounce();
                }
            }
        }
    }
}

void Coin::Break() {
    stat = BlockStat::Broken;
    drawStat = DrawStat::None;
}

void Coin::Bounce() {
    stat = BlockStat::Bouncing;
}

bool Coin::IsActive() const {
    return (stat == BlockStat::Normal);
}