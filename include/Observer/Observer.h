#ifndef OBSERVER_H
#define OBSERVER_H

#include "raylib.h"
#include "vector"
#include "ICollidable.h"
#include "../Character/Character.h"

class CollisionManager {
private:
    std::vector<ICollidable*> collidables;

    std::vector<ICollidable*> fireballs; 

    ICollidable* mainCharacter = nullptr; // e.g., Mario

public:
    void Register(ICollidable* obj) {

        if(obj == nullptr || obj->IsActive() == false) return; 
        collidables.push_back(obj);
    }

    void addFireball(ICollidable* obj){
        if(obj == nullptr || obj->IsActive() == false) return; 
        fireballs.push_back(obj); 
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




        // Check fireballs vs object
        for(auto *fireball : fireballs) if(fireball->IsActive()){
            isOnGround = false; 

            for(auto *obj : collidables) if(obj != mainCharacter){

                if (obj->IsActive() && CheckCollisionRecs(fireball->getHitbox(), obj->getHitbox())) {
                    fireball->adaptCollision(obj);
                    obj->adaptCollision(fireball);
                }
                
                if(obj -> IsActive()){
                    Rectangle rect = obj->getHitbox();
                    rect.y -= 0.2f;
                    isOnGround |= CheckCollisionRecs(fireball->getHitbox(), rect);
                }
            }
    

            if(isOnGround == false){
                Fireball *thisFireball = dynamic_cast<Fireball*>(fireball);
                thisFireball->setGroundLevel(2.0f * GetScreenHeight());
            }
        }

    }

    void Clear() {
        collidables.clear();
    }
};

#endif
