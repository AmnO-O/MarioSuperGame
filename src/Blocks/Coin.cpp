#include "Blocks/Coin.h"
#include <fstream>
#include <iostream>
#include "Character/Character.h"
#include "Resources/StatsManager.h"

ContainCoin::ContainCoin(Rectangle block) : GameObject(), coinAni(new BounceAnimation(Images::textures["mapobject.png"], block , 1.0f, 40.0f, 0.1f)) {
    std::ifstream fin;
    fin.open("assets/animation/ContainCoin.txt");
    int x, y, w, h, n;
    fin >> n;
    for (int i = 0; i < n; i++) {
        fin >> x >> y >> w >> h;
        coinAni->addRect({1.0f * x, 1.0f * y, 1.0f * w, 1.0f * h});
    }
    block.y -= h;
    coinAni->setBlockRec(block);
    hitbox = {-1, -1, 0, 0};
}

void ContainCoin::update(float delta) {
    coinAni->Update(delta);
    if (coinAni->ended()) {
        active = false;
    }
    return;
}

void ContainCoin::render() {
    coinAni->Draw();
}

void ContainCoin::printData(std::ostream &os) const{
    coinAni->save(os);
}

void ContainCoin::loadData(std::istream &is) {
    coinAni->load(is);
}

Coin::Coin(Texture2D &tex, std::istream &is) : Block(tex), ani(tex, false, 0.2f), coinAni(tex, {0, 0, 0, 0}, 1.0f, 40.0f, 0.1f) {
    int num = 0;
    is >> num;
    for (int i = 0; i < num; i++) {
        int x, y, w, h;
        is >> x >> y >> w >> h;
        ani.addRect({1.0f * x, 1.0f * y, 1.0f * w, 1.0f * h});
    }
    is >> num;
    for (int i = 0; i < num; i++) {
        int x, y, w, h;
        is >> x >> y >> w >> h;
        coinAni.addRect({1.0f * x, 1.0f * y, 1.0f * w, 1.0f * h});
    }
    is >> pos.x >> pos.y;
    Vector2 shape = ani.getCurrentShape();
    coinAni.setBlockRec({pos.x, pos.y, shape.x, shape.y});
}

Rectangle Coin::getHitbox() const {
    if (!IsActive()) return {-1, -1, 0, 0};
    Vector2 srcRect = ani.getCurrentShape();
    return { pos.x, pos.y, srcRect.x, srcRect.y };
}

void Coin::Update(float delta, Player* player) {
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
        if (dynamic_cast<Player*>(other)) {
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
    std::cout << "Get Coin\n";
    stat = BlockStat::Broken;
    drawStat = DrawStat::None;

    PlaySound(SoundManager::getInstance().coinSound);
    StatsManager::getInstance().addCoins();
    StatsManager::getInstance().addScore(20);
}

void Coin::Bounce() {
    std::cout << "Bounce Coin\n";
    stat = BlockStat::Bouncing;
    
    PlaySound(SoundManager::getInstance().coinSound);
    StatsManager::getInstance().addCoins();
    StatsManager::getInstance().addScore(20);
}

bool Coin::IsActive() const {
    return (stat == BlockStat::Normal);
}

void Coin::save(std::ostream &os) {
    os << (int)stat << " " << (int)drawStat << "\n";
    coinAni.save(os);
}

void Coin::load(std::istream &is) {
    is >> stat >> drawStat;
    coinAni.load(is);
}