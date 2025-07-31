#ifndef BLOCK_H
#define BLOCK_H

#include "raylib.h"
#include <iostream>
#include "Observer/Observer.h"

enum class BlockStat {
    Normal,
    Bouncing,
    Breaking,
    Broken
};

enum class DrawStat {
    None,
    First,
    Second
};

class Block : public ICollidable {
protected:
    DrawStat drawStat = DrawStat::First;
    Texture2D tex;
    Vector2 pos;

public:
    Block(Texture2D tex) : tex(tex) {}
    virtual void Update(float delta) = 0;
    virtual void Draw(DrawStat ds) const = 0;
    virtual ~Block() {}
};

#endif
