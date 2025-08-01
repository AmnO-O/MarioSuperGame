#ifndef QUESTION_H
#define QUESTION_H

#include "Block.h"
#include <vector>
#include "Appearance.h"
#include "Character/Animation.h"

class Question : public Block {
private:
    BounceAnimation bounceAni;
    AnimationManager ani;
    Rectangle BrokenRect;
    BlockStat stat = BlockStat::Normal;
    void Break(); // call this when hit from below by Big Mario
    void Bounce(); // call this when hit from below by Normal Mario

public:
    Question(Texture2D &tex, std::istream &is);

    Rectangle getHitbox() const override;
    void Update(float delta) override;
    void Draw(DrawStat ds) const override;
    void adaptCollision(ICollidable* other) override;

    ~Question() override {}
};

#endif