#ifndef COIN_H
#define COIN_H

#include "raylib.h"
#include "Block.h"
#include "iostream"
#include "Character/Animation.h"

class BounceCoinAnimation {
private:
    Texture tex;
    float bounceOffset = 0.0f;
    const float bounceTime = 1.0f;
    const float bounceHeight = 40.0f;
    const float delay = 0.1f;
    float frameTime = 0.0f;
    std::vector<Rectangle> recs = {};
    Rectangle blockRec;
public:
    void input(Texture2D &tex, std::istream &is, Rectangle rec) {
        this->tex = tex;
        blockRec = rec;
        int num;
        is >> num;
        for (int i = 0; i < num; i++) {
            int x, y, w, h;
            is >> x >> y >> w >> h;
            recs.push_back({1.0f * x, 1.0f * y, 1.0f * w, 1.0f * h});
        }
    }
    void Update(float delta) {
        frameTime += delta;
        if (frameTime <= bounceTime / 2)
            bounceOffset = (frameTime / (bounceTime / 2)) * bounceHeight;
        else
            if (frameTime < bounceTime)
                bounceOffset = ((bounceTime - frameTime) / (bounceTime / 2)) * bounceHeight;
            else {
                frameTime = 0;
                bounceOffset = 0;
            }
    }
    void Draw() const {
        int curframe = (int)std::floor(frameTime / delay);
        curframe %= recs.size();
        DrawTextureRec(tex, recs[curframe], {blockRec.x + (blockRec.width - recs[curframe].width) / 2, blockRec.y - bounceOffset}, WHITE);
    }
    bool ended() const { return frameTime == 0.0f; }
};

class Coin : public Block {
private:
    BounceCoinAnimation coinAni;
    AnimationManager ani;
    BlockStat stat = BlockStat::Normal;
    void Break();
    void Bounce();
    
public:
    Coin(Texture2D tex, std::istream &is);
    Rectangle getHitbox() const override;
    void Draw(DrawStat ds) const override;
    void adaptCollision(ICollidable* other) override;
    void Update(float delta) override;
    bool IsActive() const override;
    ~Coin() override {}
};

#endif
