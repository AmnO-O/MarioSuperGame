#ifndef MAP_H
#define MAP_H

#include "raylib.h"
#include <string>
#include "../Blocks/Block.h"
#include <vector>
#include "Exceptions.h"
#include "Observer/Observer.h"
#include "Character/Character.h"
#include "Character/Enemy.h"

class Map {
private:
    int space;
    int curspace = 0;
    Texture2D background;
    std::vector<Block*> blocks;
    Player *character;
    std::vector<Enemy*> enemies;

    void input(std::istream &is, Texture2D &objectTex);
public:
    Map() = delete;
    Map(const std::string& folderPath, Texture2D &objectTex);
    Vector2 getSize() const { return {1.0f * background.width, 1.0f * background.height / space}; }

    void SetUp(Player* player);
    void Update(float delta);
    void Draw() const;
    void Unload();
};

#endif
