#ifndef FLOOR_H
#define FLOOR_H

#include "raylib.h"
#include "Block.h"
#include "iostream"

class Floor : public Block {
private:
    Rectangle srcRect;
    int num;
    
public:
    Floor(Texture2D tex, std::istream &is);
    Rectangle getHitbox() const override;
    void Draw(DrawStat ds) const override;
    void adaptCollision(ICollidable* other) override {}
    void Update(float delta) override;
    ~Floor() override {}
};

#endif
