#ifndef BRIDGE_H
#define BRIDGE_H

#include "raylib.h"
#include "Block.h"
#include "iostream"
#include "Character/PlayerAction.h"

class Bridge : public Block {
protected:
    AnimationManager ani;
    Rectangle body;
    Vector2 bodyPos;
    float width;
    BlockStat stat = BlockStat::Normal;
    bool hasBroken = false;
    
public:
    Bridge(Texture2D &tex, std::istream &is);
    void save(std::ostream &os) override;
    void load(std::istream &is) override;
    Rectangle getHitbox() const override;
    void changePlayerPos(PlayerActionManager &pm) override;
    void Draw(DrawStat ds) const override;
    void adaptCollision(ICollidable* other) override {}
    void Update(float delta, Player* player) override;
    ~Bridge() override = default;
};

#endif