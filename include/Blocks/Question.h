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
    STAR,
    NORMAL
};

class Question : public Block {
private:
    BounceAnimation bounceAni;
    BounceAnimation brokenAni;
    AnimationManager ani;

    Rectangle BrokenRect;
    BlockStat stat = BlockStat::Normal;
    QuestionType type;
    Creator* creator = nullptr;
    std::vector<GameObject*> objects = {};
    int num;

    void clearObj();
    void Break(Player* player); 

public:
    Question(Texture2D &tex, std::istream &is);

    void save(std::ostream &os) override;
    void load(std::istream &is) override;
    Rectangle getHitbox() const override;
    void Update(float delta, Player* player) override;
    void Draw(DrawStat ds) const override;
    void adaptCollision(ICollidable* other) override;

    ~Question() override {
        if (creator)
            delete creator;
        for (auto obj : objects) 
            if (obj)
                delete obj;
    }
};

#endif