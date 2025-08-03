#ifndef BRICK_H
#define BRICK_H

#include "Block.h"
#include <vector>
#include "Animation/Appearance.h"

class Brick : public Block {
private:
    BounceAnimation bounceAni;
    const float gravity = 800.0f;
    const float rotateTime = 0.2f;
    const Vector2 initVelocity = {50.0f, -150.0f};
    Vector2 fragmentVelocity = {0, 0};
    std::vector <Vector2> fragmentPos;

    Rectangle srcRect;
    Rectangle fragmentRect;
    BlockStat stat = BlockStat::Normal;
    float frameTime = 0.0f;
    void Break(); // call this when hit from below by Big Mario
    void Bounce(); // call this when hit from below by Normal Mario
    void DrawFragment() const;

public:
    Brick(Texture2D &tex, std::istream &is);

    Rectangle getHitbox() const override;
    void Update(float delta) override;
    void Draw(DrawStat ds) const override;
    void adaptCollision(ICollidable* other) override;

    bool IsActive() const override;
    ~Brick() override {}
};

#endif