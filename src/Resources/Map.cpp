#include "Resources/Map.h"
#include "Blocks/Brick.h"
#include "Blocks/Floor.h"
#include "Blocks/Coin.h"
#include "Blocks/Sewer.h"
#include "Blocks/Question.h"
#include <fstream>

void Map::input(std::istream &is, Texture2D &objectTex) {
    is >> space;
    cam = new MyCamera2D(1.0f * GetScreenWidth(), 1.0f * GetScreenHeight()); 
    cam->setMapSize(getSize());

    std::string s;
    int nBlock;
    is >> nBlock;
    for (int j = 0; j < nBlock; j++) {
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
        else if (s == "COIN") {
            for (int i = 0; i < n; i++)
                blocks.push_back(new Coin(objectTex, is));
        }
        else if (s == "QUESTION") {
            for (int i = 0; i < n; i++)
                blocks.push_back(new Question(objectTex, is));
        }
        else if (s == "SEWER") {
            for (int i = 0; i < n; i++)
                blocks.push_back(new Sewer(objectTex, is));
        }
        else if (s == "H_SEWER") {
            for (int i = 0; i < n; i++)
                blocks.push_back(new HorizontalSewer(objectTex, is));
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
    CollisionManager::getInstance().Register(character->shootFireball()); 
    CollisionManager::getInstance().CheckAllCollisions();
    for (int i = 0; i < blocks.size(); i++) {
        blocks[i]->Update(delta, character);
        Vector2 tmpCam = blocks[i]->changeCam();
        Vector2 tmpPos = blocks[i]->changePlayerPos();
        if (tmpPos.x >= 0 && tmpPos.y >= 0 && tmpCam.x >= 0 && tmpCam.y >= 0) {
            character->setGroundLevel(2.0f * GetScreenHeight());
            character->setPosition(tmpPos);
            cam->setTarget(tmpCam);
        }

    }
        
    if(character)
        character->update(delta); 

    for (int i = (int)enemies.size() - 1; i >= 0; i--) {
        enemies[i]->update(delta);
    }
    
    cam -> update(character); 
}

void Map::Draw() const {    
    
    Camera2D camera = cam ->getCamera(); 
    BeginMode2D(camera); 

        DrawTexture(background, 0, 0, WHITE);

    
        if( dynamic_cast<Player*> (character) &&  dynamic_cast<Player*> (character)->hidePlayer()){
            character->render(); 
        }

        for (int i = 0; i < blocks.size(); i++) {
            blocks[i]->Draw(DrawStat::First);
        }
        
        for (int i = 0; i < blocks.size(); i++) {
            blocks[i]->Draw(DrawStat::Second);
        }

        if( dynamic_cast<Player*> (character) &&  !dynamic_cast<Player*> (character)->hidePlayer()){
            character->render(); 
        }


        for (int i = 0; i < enemies.size(); i++) {
            enemies[i]->render();
            // DrawRectangleLines(enemies[i]->getHitbox().x, enemies[i]->getHitbox().y, 
            //                     enemies[i]->getHitbox().width, enemies[i]->getHitbox().height, GREEN);
        }
    
    EndMode2D(); 
}

void Map::Unload() {
    UnloadTexture(background);
    for (int i = 0; i < blocks.size(); i++)
        delete blocks[i];

    for (int i = 0; i < enemies.size(); i++) {
        delete enemies[i];
    }

    delete cam;
}

void Map::SetUp(Player* player) {
    CollisionManager::getInstance().Clear();
    CollisionManager::getInstance().SetMainCharacter(player);
    for (int i = 0; i < blocks.size(); i++)
        CollisionManager::getInstance().Register(blocks[i]);
    character = player;

    for (int i = 0; i < enemies.size(); i++) 
        CollisionManager::getInstance().Register(enemies[i]);
}