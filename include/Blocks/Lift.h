#ifndef LIFT_H
#define LIFT_H

#include "raylib.h"
#include "Block.h"
#include "iostream"
#include "Character/PlayerAction.h"

class Lift : public Block {
private:
    bool canBack = false;
    Vector2 start;
    Vector2 des;
    Rectangle srcRect;
    int width;
    Vector2 velocity = {20.0f, 20.0f};
    
public:
    Lift(Texture2D &tex, std::istream &is);
    Rectangle getHitbox() const override;
    void Draw(DrawStat ds) const override;
    void adaptCollision(ICollidable* other) override {}
    void Update(float delta, Player* player) override;
    ~Lift() override = default;
};

#endif
