#include "Map.h"
#include "Blocks/Brick.h"
#include "Blocks/Floor.h"
#include <fstream>

void Map::input(std::istream &is, Texture objectTex) {
    is >> space;
    std::string s;
    while (is >> s) {
        int n;
        is >> n;
        if (s == "BRICK") {
            for (int i = 0; i < n; i++)
                blocks.push_back(new Brick(objectTex, is));
        }
        else if (s == "FLOOR") {
            for (int i = 0; i < n; i++)
                blocks.push_back(new Floor(objectTex, is));
        }
        else if (s == "GOOMBA") {
            for (int i = 0; i < n; i++) {
                float x, y;
                is >> x >> y;
                enemies.push_back(new Goomba({x, y}));
            }
        }
    }
}

Map::Map(const std::string& folderPath, Texture objectTex) {
    std::string path = folderPath + "/map.png";
    background = LoadTexture(path.c_str());
    path = folderPath + "/info.txt";
    std::ifstream fin;
    fin.open(path);
    if (!fin.is_open())
        throw ResourceException("Can't load map info");
    input(fin, objectTex);
    fin.close();
}

void Map::Update(float delta) {
    for (int i = 0; i < blocks.size(); i++)
        blocks[i]->Update(delta);

    for (int i = 0; i < enemies.size(); i++)
        enemies[i]->update(delta);
}

void Map::Draw() const {    
    Rectangle src = {
        0,
        0,
        1.0f * GetScreenWidth(),
        1.0f * GetScreenHeight()
    };

    Rectangle dest = src;

    Vector2 origin = { 0.0f, 0.0f };
    DrawTexturePro(background, src, dest, origin, 0.0f, WHITE);

    for (int i = 0; i < blocks.size(); i++) {
        blocks[i]->Draw(DrawStat::First);
    }
    
    for (int i = 0; i < blocks.size(); i++) {
        blocks[i]->Draw(DrawStat::Second);
    }

    for (int i = 0; i < enemies.size(); i++) {
        enemies[i]->render();
    }
}

void Map::Unload() {
    UnloadTexture(background);
    for (int i = 0; i < blocks.size(); i++)
        delete blocks[i];

    for (int i = 0; i < enemies.size(); i++)
        delete enemies[i];
}

void Map::SetUp(CollisionManager &cm, Player* player) const {
    cm.Clear();
    cm.SetMainCharacter(player);
    for (int i = 0; i < blocks.size(); i++)
        cm.Register(blocks[i]);

    for (int i = 0; i < enemies.size(); i++) 
        cm.Register(enemies[i]);
}