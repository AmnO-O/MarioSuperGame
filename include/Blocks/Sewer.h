#ifndef SEWER_H
#define SEWER_H

#include "raylib.h"
#include "Block.h"
#include "iostream"

class Sewer : public Block {
private:
    Rectangle head;
    Rectangle body;
    int height;
    
public:
    Sewer(Texture2D &tex, std::istream &is);
    Rectangle getHitbox() const override;
    void Draw(DrawStat ds) const override;
    void adaptCollision(ICollidable* other) override {}
    void Update(float delta) override;
    ~Sewer() override {}
};

#endif
