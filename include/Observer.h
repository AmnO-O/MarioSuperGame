#ifndef OBSERVER_H
#define OBSERVER_H

#include "raylib.h"
#include "vector"

class ICollidable {
public:
    virtual Rectangle getHitbox() const = 0;
    virtual void adaptCollision(ICollidable* other) = 0;
    virtual bool IsActive() const { return true; } 
    virtual ~ICollidable() = default;
};

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

        // Check character vs all others
        for (auto* obj : collidables) {
            if (obj != mainCharacter && obj->IsActive() && CheckCollisionRecs(mainCharacter->getHitbox(), obj->getHitbox())) {
                mainCharacter->adaptCollision(obj);
                obj->adaptCollision(mainCharacter);
            }
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
