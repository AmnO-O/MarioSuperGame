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
    Texture2D &tex;
    Vector2 pos;

public:
    Block(Texture2D &tex) : tex(tex) {}
    virtual Vector2 changeCam() {return {-1.0f, -1.0f};}
    virtual Vector2 changePlayerPos() {return {-1.0f, -1.0f};}
    virtual void Update(float delta, Player* player) = 0;
    virtual void Draw(DrawStat ds) const = 0;
    virtual ~Block() {}
};

#endif
