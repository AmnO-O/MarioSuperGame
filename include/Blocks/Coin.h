#ifndef COIN_H
#define COIN_H

#include "raylib.h"
#include "Block.h"
#include "iostream"
#include "Animation/Animation.h"
#include "Animation/Appearance.h"
#include "Object/GameObject.h"
#include <vector>

class ContainCoin : public GameObject {
private:
    BounceAnimation *coinAni;
public:
    ~ContainCoin() { if (coinAni) delete coinAni;}
    ContainCoin(Rectangle block);    
    Vector2 getPosition() const { return coinAni->getPosition(); }
    virtual void setGroundLevel(float groundLevel) {}
    void update(float deltaTime) override;
    void render() override;
};

class Coin : public Block {
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
    void isHitBelow(ICollidable* block) override { Bounce(); }
    ~Coin() override {}
};

#endif
