#include "Map.h"
#include "Blocks/Brick.h"
#include "Blocks/Floor.h"
#include "Observer/Observer.h"
#include <fstream>

void Map::input(std::istream &is, Texture objectTex) {
    is >> space;
    std::string s;
    for (int j = 0; j < space; j++) {
        is >> s;
        int n; is >> n;
        if (s == "BRICK") {
            for (int i = 0; i < n; i++)
                blocks.push_back(new Brick(objectTex, is));
        }
        else if (s == "FLOOR") {
            for (int i = 0; i < n; i++)
                blocks.push_back(new Floor(objectTex, is));
        }
    }

    int nEnemy;
    is >> nEnemy;
    while (is >> s) {
        int n; is >> n;
        if (s == "GOOMBA") {
            for (int i = 0; i < n; i++) {
                int x, y;
                is >> x >> y;
                enemies.push_back(new Goomba({x * 1.0f, y * 1.0f}));
            }
        }
        else if (s == "KOOPA") {
            for (int i = 0; i < n; i++) {
                int x, y;
                is >> x >> y;
                enemies.push_back(new Koopa({x * 1.0f, y * 1.0f}));
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

void Map::Update(float delta, CollisionManager &cm) {
    for (int i = 0; i < blocks.size(); i++)
        blocks[i]->Update(delta);

    // Update enemies and remove dead ones
    for (int i = enemies.size() - 1; i >= 0; i--) {
        enemies[i]->update(delta);
        
        // Remove enemy if dead
        if (enemies[i]->isDead()) {
            // Unregister from collision manager before deleting
            cm.Unregister(enemies[i]);
            delete enemies[i];
            enemies.erase(enemies.begin() + i);
        }
    }
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
        // DrawRectangleLines(enemies[i]->getHitbox().x, enemies[i]->getHitbox().y, 
        //                     enemies[i]->getHitbox().width, enemies[i]->getHitbox().height, GREEN);
    }
}

void Map::Unload() {
    UnloadTexture(background);
    for (int i = 0; i < blocks.size(); i++)
        delete blocks[i];

    for (int i = 0; i < enemies.size(); i++) {
        delete enemies[i];
    }
}

void Map::SetUp(CollisionManager &cm, Player* player) const {
    cm.Clear();
    cm.SetMainCharacter(player);
    for (int i = 0; i < blocks.size(); i++)
        cm.Register(blocks[i]);

    for (int i = 0; i < enemies.size(); i++) 
        cm.Register(enemies[i]);
}