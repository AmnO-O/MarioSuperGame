#ifndef APPEARANCE_H
#define APPEARANCE_H

#include "raylib.h"
#include "iostream"
#include <vector>
#include "Exceptions.h"

class AppearanceAnimation {
protected:
    Texture2D &tex;
    float offset = 0.0f;
    const float time;
    const float height;
    const float delay;
    float frameTime = 0.0f;
    std::vector<Rectangle> recs = {};
    Rectangle blockRec;
public:
    AppearanceAnimation(Texture2D &tex, Rectangle block, float time, float height, float delay) : tex(tex), blockRec(block), time(time), height(height), delay(delay) {}
    void addRect(Rectangle rec) {
        recs.push_back(rec);
    }
    virtual void Update(float delta) {
        frameTime += delta;
        if (frameTime < time)
            offset = (frameTime / time) * height;
        else {
            frameTime = 0;
            offset = 0;
        }
    }
    virtual void Draw() const {
        if (recs.size() == 0) throw GameException("Appearance doesn't init recs!");
        int curframe = (int)std::floor(frameTime / delay);
        curframe %= recs.size();
        Rectangle rec = recs[curframe];
        rec.height = offset;
        DrawTextureRec(tex, rec, {blockRec.x + (blockRec.width - recs[curframe].width) / 2, blockRec.y - offset}, WHITE);
    }
    Vector2 getPosition() const {
        if (recs.size() == 0) throw GameException("Appearance doesn't init recs!");
        int curframe = (int)std::floor(frameTime / delay);
        curframe %= recs.size();
        return {blockRec.x + (blockRec.width - recs[curframe].width) / 2, blockRec.y - offset};
    }
    void setBlockRec(Rectangle block) {
        blockRec = block;
    }
    bool ended() const { return frameTime == 0.0f; }
};

class BounceAnimation : public AppearanceAnimation {
public:
    BounceAnimation(Texture2D &tex, Rectangle block, float time, float height, float delay) : AppearanceAnimation(tex, block, time, height, delay) {}
    void Update(float delta) override {
        frameTime += delta;
        if (frameTime <= time / 2)
            offset = (frameTime / (time / 2)) * height;
        else
            if (frameTime < time)
                offset = ((time - frameTime) / (time / 2)) * height;
            else {
                frameTime = 0;
                offset = 0;
            }
    }
    void Draw() const override {
        if (recs.size() == 0) throw GameException("Appearance doesn't init recs!");
        int curframe = (int)std::floor(frameTime / delay);
        curframe %= recs.size();
        DrawTextureRec(tex, recs[curframe], {blockRec.x + (blockRec.width - recs[curframe].width) / 2, blockRec.y - offset}, WHITE);
    }
};

#endif
