#pragma once
#include <vector>
#include "raylib.h"
#include "Fireball.h"

class FireballManager {
    std::vector<Fireball*> fireballs;
    void cleanFireballs();

public:
    FireballManager();
    ~FireballManager();

    void printData(std::ostream &fout) const;
    void loadData(std::istream &fin);
    void update(float deltaTime);
    Fireball* shootFireball(Vector2 playerPosition, bool isFacingRight);
    void render();
};
