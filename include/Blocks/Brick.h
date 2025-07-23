#ifndef BRICK_H
#define BRICK_H

#include "Block.h"
#include <vector>

class Brick : public Block {
private:
    float bounceOffset = 0.0f;
    const float bounceTime = 0.25f;
    const float bounceHeight = 6;
    const float gravity = 800.0f;
    const float rotateTime = 0.2f;
    const Vector2 initVelocity = {150.0f, -300.0f};
    Vector2 fragmentVelocity = {0, 0};
    std::vector <Vector2> fragmentPos;

    Rectangle srcRect;
    Rectangle fragmentRect;
    BlockStat stat = BlockStat::Normal;
    float frameTime = 0.0f;

public:
    Brick(Texture2D tex, std::istream &is);

    Rectangle getHitbox() const override;
    void Update(float delta) override;
    void Draw(DrawStat ds) const override;
    void DrawFragment() const;
    void adaptCollision(ICollidable* other) override;

    bool IsActive() const override;
    void Break(); // call this when hit from below by Big Mario
    void Bounce(); // call this when hit from below by Normal Mario
    ~Brick() override {}
};

#endif