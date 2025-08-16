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
protected:
    Rectangle BrokenRect;
    BlockStat stat = BlockStat::Normal;
    void Break(Player* player); 
private:
    BounceAnimation brokenAni;
    BounceAnimation bounceAni;
    AnimationManager ani;

    QuestionType type;
    Creator* creator = nullptr;
    std::vector<GameObject*> objects = {};
    int num;

    void clearObj();

public:
    Question(Texture2D &tex, std::istream &is);

    void save(std::ostream &os) override;
    void load(std::istream &is) override;
    virtual Rectangle getHitbox() const ;
    virtual void Update(float delta, Player* player) ;
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