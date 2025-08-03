#ifndef QUESTION_H
#define QUESTION_H

#include "Block.h"
#include <vector>
#include "Animation/Appearance.h"
#include "Animation/Animation.h"
#include "Object/Creator.h"

enum class QuestionType {
    COIN,
    POWER,
    STAR
};

class Question : public Block {
private:
    BounceAnimation bounceAni;
    AnimationManager ani;

    Rectangle BrokenRect;
    BlockStat stat = BlockStat::Normal;
    QuestionType type;
    Creator* creator = nullptr;
    GameObject* object = nullptr;
    int num;

    void Break(Player* player); 

public:
    Question(Texture2D &tex, std::istream &is);

    Rectangle getHitbox() const override;
    void Update(float delta) override;
    void Draw(DrawStat ds) const override;
    void adaptCollision(ICollidable* other) override;

    ~Question() override {
        if (creator)
            delete creator;
        if (object)
            delete object;
    }
};

#endif