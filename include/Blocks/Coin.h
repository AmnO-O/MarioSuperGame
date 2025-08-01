#ifndef COIN_H
#define COIN_H

#include "raylib.h"
#include "Block.h"
#include "iostream"
#include "Character/Animation.h"
#include "Appearance.h"
#include "Character/GameObject.h"

class Coin : public Block, public GameObject {
private:
    BounceAnimation coinAni;
    AnimationManager ani;
    BlockStat stat = BlockStat::Normal;
    void Break();
    void Bounce();
    
public:
    Coin(Texture2D &tex, std::istream &is);
    Rectangle getHitbox() const override;
    void Draw(DrawStat ds) const override;
    void adaptCollision(ICollidable* other) override;
    void Update(float delta) override;
    bool IsActive() const override;
    void render() override {}
    void isHitBelow() override { Bounce(); }
    ~Coin() override {}
};

#endif
