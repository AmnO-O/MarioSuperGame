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
#include "MyCamera2D.h"
#include <queue>
#include "Blocks/Flag.h"

class Map {
private:
    bool ended = false;
    int space;
    int curspace = 0;
    Texture2D background;
    float des;

    MyCamera2D* cam;
    std::deque<Vector3> camChange;

    std::vector<Block*> blocks;
    std::deque<Enemy*> enemies;
    std::vector<Enemy*> curEnemies;
    Player *character;
    PlayerActionManager pm;

    void input(std::istream &is, Texture2D &objectTex);
    void spawnEnemy();
public:
    Map() = delete;
    Map(const std::string& folderPath, Texture2D &objectTex);
    Vector2 getSize() const { return {1.0f * background.width, 1.0f * background.height / space}; }

    void save(std::ostream &os);
    void load(std::istream &is);
    void SetUp(Player* player);
    void Update(float delta);
    void Draw() const;
    void Unload();
    bool isEnd();
    Flag* getFlag() const;
};

#endif