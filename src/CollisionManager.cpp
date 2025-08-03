#include "Observer/Observer.h"
#include "Blocks/Block.h"
#include "Blocks/Coin.h"

float CollisionManager::overlap(Rectangle charBox, Rectangle objBox) {
    // Compute intersection rectangle
    float x1 = std::max(charBox.x, objBox.x);
    float y1 = std::max(charBox.y, objBox.y);
    float x2 = std::min(charBox.x + charBox.width, objBox.x + objBox.width);
    float y2 = std::min(charBox.y + charBox.height, objBox.y + objBox.height);

    float overlapWidth = x2 - x1;
    float overlapHeight = y2 - y1;
    float area = overlapWidth * overlapHeight;
    if (area > 0)
        return area;
    return 0;
}

void CollisionManager::RemoveInactive() {
    collidables.erase(
        std::remove_if(collidables.begin(), collidables.end(),
            [](ICollidable* obj) {
                return obj == nullptr || !obj->IsActive();
            }),
        collidables.end()
    );
}

void CollisionManager::CheckCharObj() {
    if (!mainCharacter) return;
    Player *player = dynamic_cast<Player*>(mainCharacter);
    bool isOnGround = false; 

    ICollidable* mostOverlapObj = nullptr;
    float maxOverlap = 0.0f;

    // Check character vs all others
    for (auto* obj : collidables) {
        if (obj != mainCharacter && obj->IsActive() && CheckCollisionRecs(mainCharacter->getHitbox(), obj->getHitbox())) {
            float curOverlap = overlap(mainCharacter->getHitbox(), obj->getHitbox());
            if (curOverlap > maxOverlap) {
                mostOverlapObj = obj;
                maxOverlap = curOverlap;    
            }
        }

        if(obj != mainCharacter && obj -> IsActive()){
            Rectangle rect = obj->getHitbox();
            rect.y -= 1.0f; 
            isOnGround |= CheckCollisionRecs(mainCharacter->getHitbox(), rect);
        }
    }

    if (mostOverlapObj) {
        mainCharacter->adaptCollision(mostOverlapObj);
        mostOverlapObj->adaptCollision(mainCharacter);
    }

    if(isOnGround == false){
        player->setGroundLevel(2.0f * GetScreenHeight());
    }
}

void CollisionManager::CheckObjObj() {
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
        GameObject* p = dynamic_cast<GameObject*>(collidables[i]);
        if (p) {
            bool isOnGround = false;
            for (auto* obj : collidables) 
                if (obj != collidables[i] && dynamic_cast<Block*>(obj) && !dynamic_cast<Coin*>(obj)) {
                    Rectangle rect = obj->getHitbox();
                    rect.y -= 1.0f; 
                    isOnGround |= CheckCollisionRecs(p->getHitbox(), rect);
                }
            if (!isOnGround)
                p->setGroundLevel(2.0f * GetScreenHeight());
        }
    }
}

void CollisionManager::CheckAllCollisions() {
    RemoveInactive();
    CheckCharObj();
    CheckObjObj();
}

void CollisionManager::NotifyAbove(ICollidable* base) {
    Rectangle baseHitbox = base->getHitbox();
    Rectangle aboveBox = {
        baseHitbox.x,
        baseHitbox.y - 5,          // a little space above the block
        baseHitbox.width,
        5
    };

    for (auto* obj : collidables) {
        if (obj == base || !obj->IsActive()) continue;

        Rectangle objBox = obj->getHitbox();
        if (CheckCollisionRecs(aboveBox, objBox)) {
            obj->isHitBelow();
        }
    }
}