#ifndef FLAG_H
#define FLAG_H

#include "raylib.h"
#include "Block.h"
#include "iostream"
#include "Character/PlayerAction.h"
#include <memory>

class Flag : public Block {
protected:
    float time = 0.0f;
    float frametime = 0.0f;
    bool hasClimb = false;
    Vector2 tp = {-1.0f, -1.0f};
    Rectangle head;
    Rectangle body;
    int height;
    
    std::unique_ptr<PlayerActionManager> animationClimbFlag; 
public:
    Flag(Texture2D &tex, std::istream &is, float time);
    Rectangle getHitbox() const override;
    Vector2 changeCam() override;
    Vector2 changePlayerPos() override;
    void Draw(DrawStat ds) const override;
    void adaptCollision(ICollidable* other) override;
    void Update(float delta, Player* player) override;
    ~Flag() override = default; 
};

#endif
