#ifndef SEWER_H
#define SEWER_H

#include "raylib.h"
#include "Block.h"
#include "iostream"
#include "Character/PlayerAction.h"

class Sewer : public Block {
private:
    bool canDown = false;
    bool hasDowned = false;
    Vector2 tp = {-1.0f, -1.0f};
    Vector2 cam = {-1.0f, -1.0f};
    Rectangle head;
    Rectangle body;
    int height;
    
    PlayerActionManager animationEnterSewer; 
public:
    Sewer(Texture2D &tex, std::istream &is);
    Rectangle getHitbox() const override;
    Vector2 changeCam() override;
    Vector2 changePlayerPos() override;
    void Draw(DrawStat ds) const override;
    void adaptCollision(ICollidable* other) override {}
    void Update(float delta, Player* player) override;
    ~Sewer() override {}
};

#endif
