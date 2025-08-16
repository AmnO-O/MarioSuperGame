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
    Rectangle head;
    Rectangle body;
    int height;
    
public:
    Flag(Texture2D &tex, std::istream &is, float time);
    void save(std::ostream &os) override;
    void load(std::istream &is) override;
    Rectangle getHitbox() const override;
    // Vector2 changeCam() override;
    // Vector2 changePlayerPos() override;
    void Draw(DrawStat ds) const override;
    void adaptCollision(ICollidable* other) override;
    void Update(float delta, Player* player) override;
    ~Flag() override = default; 
    std::unique_ptr<PlayerActionManager> animationClimbFlag; 
};

#endif
