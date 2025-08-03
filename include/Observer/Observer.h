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
    float overlap(Rectangle charBox, Rectangle objBox);
    void RemoveInactive();
    void CheckCharObj();
    void CheckObjObj();
    CollisionManager() = default;

public:
    CollisionManager(const CollisionManager&) = delete;
    CollisionManager& operator=(const CollisionManager&) = delete;

    // Singleton accessor
    static CollisionManager& getInstance() {
        static CollisionManager instance; // Created once, thread‑safe in C++11+
        return instance;
    }

    void Register(ICollidable* obj) { collidables.push_back(obj); }
    void SetMainCharacter(ICollidable* character) { mainCharacter = character; }
    void CheckAllCollisions();
    void Clear() { collidables.clear(); }
    void NotifyAbove(ICollidable* base);
};

#endif
