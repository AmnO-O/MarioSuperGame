#ifndef MAP_HPP
#define MAP_HPP

#include "raylib.h"
#include <string>
// #include "Block.hpp"
// #include "Floor.hpp"
// #include "Brick.hpp"
#include <vector>
#include "Exceptions.h"
// #include "CollisionManager.hpp"

class Map {
private:
    int space;
    int curspace = 0;
    Texture2D background;

    void input(std::istream &is);
    // std::vector<Block*> blocks;
public:
    Map() = delete;
    Map(const std::string& folderPath);
    Vector2 getSize() const { return {1.0f * background.width, 1.0f * background.height / space}; }

    void Update(float delta);
    void Draw() const;
    void Unload();

    friend class GameManager;
};

#endif
