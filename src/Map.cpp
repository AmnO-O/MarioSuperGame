#include "Map.h"
#include "Blocks/Brick.h"
#include "Blocks/Floor.h"
#include "Blocks/Coin.h"
#include "Blocks/Question.h"
#include <fstream>

void Map::input(std::istream &is, Texture2D &objectTex) {
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
        else if (s == "COIN") {
            for (int i = 0; i < n; i++)
                blocks.push_back(new Coin(objectTex, is));
        }
        else if (s == "QUESTION") {
            for (int i = 0; i < n; i++)
                blocks.push_back(new Question(objectTex, is));
        }
    }
}

Map::Map(const std::string& folderPath, Texture2D &objectTex) {
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
        
    if(character)
        character->update(delta); 
}

void Map::Draw() const {    
    DrawTexture(background, 0, 0, WHITE);

    for (int i = 0; i < blocks.size(); i++) {
        blocks[i]->Draw(DrawStat::First);
    }
    
    for (int i = 0; i < blocks.size(); i++) {
        blocks[i]->Draw(DrawStat::Second);
    }

    if(character)
        character->render(); 
}

void Map::Unload() {
    UnloadTexture(background);
    for (int i = 0; i < blocks.size(); i++)
        delete blocks[i];
}

void Map::SetUp(Character* player) {
    CollisionManager::getInstance().Clear();
    CollisionManager::getInstance().SetMainCharacter(player);
    for (int i = 0; i < blocks.size(); i++)
        CollisionManager::getInstance().Register(blocks[i]);
    character = player;
}