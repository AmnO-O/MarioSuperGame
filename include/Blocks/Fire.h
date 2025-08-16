#ifndef FIRE_H
#define FIRE_H

#include "raylib.h"
#include "Block.h"
#include "iostream"

class Fire : public Block {
private:
    Rectangle srcRect;
    Vector2 center;
    float frametime = 0.0f;
    float spinPeriod = 0.5f;
    float rotatePeriod = 3.0f;
    bool right = true;
    float angle = 0.0f;
    
public:
    Fire(Texture2D &tex, std::istream &is);
    Rectangle getHitbox() const override;
    void Draw(DrawStat ds) const override;
    void adaptCollision(ICollidable* other) override {}
    void Update(float delta, Player* player) override;
    void save(std::ostream &os) override;
    void load(std::istream &is) override;
    ~Fire() override {}
};

#endif
