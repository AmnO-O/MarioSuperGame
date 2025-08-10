#ifndef SEWER_H
#define SEWER_H

#include "raylib.h"
#include "Block.h"
#include "iostream"
#include "Character/PlayerAction.h"

class Sewer : public Block {
protected:
    bool canDown = false;
    bool hasDowned = false;
    Vector2 tp = {-1.0f, -1.0f};
    Vector2 cam = {-1.0f, -1.0f};
    Rectangle head;
    Rectangle body;
    int height;
    
    // PlayerActionManager animationEnterSewer; 
public:
    Sewer(Texture2D &tex, std::istream &is);
    Rectangle getHitbox() const override;
    void changeCam(std::queue<Vector3> &camChange) override;
    void changePlayerPos(PlayerActionManager &pm) override;
    void Draw(DrawStat ds) const override;
    void adaptCollision(ICollidable* other) override {}
    void Update(float delta, Player* player) override;
    ~Sewer() override = default;
};

class HorizontalSewer : public Sewer {
private:
    bool isDown;
public:
    HorizontalSewer(Texture2D &tex, std::istream &is) : Sewer(tex, is) { is >> isDown; }
    Rectangle getHitbox() const override;
    void changeCam(std::queue<Vector3> &camChange) override;
    void changePlayerPos(PlayerActionManager &pm) override;
    void Draw(DrawStat ds) const override;
    void Update(float delta, Player* player) override;
    ~HorizontalSewer() override = default;
};

#endif
