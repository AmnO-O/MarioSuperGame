#ifndef OBSERVER_H
#define OBSERVER_H

#include "raylib.h"
#include "vector"
#include "ICollidable.h"
#include "Character/Character.h"

class CollisionManager {
private:
    std::vector<ICollidable*> collidables;
    ICollidable* mainCharacter = nullptr; // e.g., Mario

public:
    void Register(ICollidable* obj) {
        collidables.push_back(obj);
    }

    void SetMainCharacter(ICollidable* character) {
        mainCharacter = character;
    }

    void CheckAllCollisions() {
        if (!mainCharacter) return;
        Player *player = dynamic_cast<Player*>(mainCharacter);
        bool isOnGround = false;

        // Check character vs all others
        for (auto* obj : collidables) {
            if (obj != mainCharacter && obj->IsActive() && CheckCollisionRecs(mainCharacter->getHitbox(), obj->getHitbox())) {
                mainCharacter->adaptCollision(obj);
                obj->adaptCollision(mainCharacter);
            }

            if(obj != mainCharacter && obj -> IsActive()){
                Rectangle rect = obj->getHitbox();
                rect.y -= 0.2f;
                isOnGround |= CheckCollisionRecs(mainCharacter->getHitbox(), rect);
            }
        }

        if(isOnGround == false){
            player->setGroundLevel(2.0f * GetScreenHeight());
        }

        // Check object vs object
        for (int i = 0; i < collidables.size(); ++i) {
            for (int j = i + 1; j < collidables.size(); ++j) {
                auto* a = collidables[i];
                auto* b = collidables[j];
                if (a->IsActive() && b->IsActive() && CheckCollisionRecs(a->getHitbox(), b->getHitbox())) {
                    a->adaptCollision(b);
                    b->adaptCollision(a);
                }
            }
        }
    }

    void Clear() {
        collidables.clear();
    }
};

#endif
