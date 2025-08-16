#ifndef BLOCK_H
#define BLOCK_H

#include "raylib.h"
#include <iostream>
#include "Observer/Observer.h"
#include "Character/PlayerAction.h"

enum class BlockStat {
    Normal,
    Bouncing,
    Breaking,
    Broken
};

inline std::istream& operator>>(std::istream &is, BlockStat &b) {
    int val;
    is >> val;
    b = static_cast<BlockStat>(val);
    return is;
}

enum class DrawStat {
    None,
    Zero,
    First,
    Second
};

inline std::istream& operator>>(std::istream &is, DrawStat &b) {
    int val;
    is >> val;
    b = static_cast<DrawStat>(val);
    return is;
}

class Block : public ICollidable {
protected:
    DrawStat drawStat = DrawStat::Zero;
    Texture2D &tex;
    Vector2 pos;

public:
    Block(Texture2D &tex) : tex(tex) {}
    virtual void save(std::ostream &os) = 0;
    virtual void load(std::istream &is) = 0;
    virtual void changeCam(std::deque<Vector3> &camChange) {return;}
    virtual void changePlayerPos(PlayerActionManager &pm) {return;}
    virtual void Update(float delta, Player* player) = 0;
    virtual void Draw(DrawStat ds) const = 0;
    virtual ~Block() {}
};

#endif
