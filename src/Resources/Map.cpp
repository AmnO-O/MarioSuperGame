#include "Resources/Map.h"
#include "Blocks/Brick.h"
#include "Blocks/Floor.h"
#include "Blocks/Coin.h"
#include "Blocks/Sewer.h"
#include "Blocks/Question.h"
#include "Character/Goomba.h"
#include "Character/Koopa.h"
#include "Character/Piranha.h"
#include "Character/EnemyFactory.h"
#include "Blocks/Flag.h"
#include <fstream>

void Map::input(std::istream &is, Texture2D &objectTex) {
    is >> space >> des;
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
        else if (s == "FLAG") {
            for (int i = 0; i < n; i++)
                blocks.push_back(new Flag(objectTex, is, 1.1f));
        }
    }

    int nEnemy;
    is >> nEnemy;
    while (is >> s) {
        int n; is >> n;
        std::unique_ptr<EnemyFactory> factory;

        if (s == "GOOMBA") {
            factory = std::make_unique<GoombaFactory>();
            for (int i = 0; i < n; i++) {
                int x, y;
                is >> x >> y;
                enemies.push_back(factory->createEnemy({x * 1.0f, y * 1.0f}).release());
            }
        }
        else if (s == "KOOPA") {
            factory = std::make_unique<KoopaFactory>();
            for (int i = 0; i < n; i++) {
                int x, y;
                is >> x >> y;
                enemies.push_back(factory->createEnemy({x * 1.0f, y * 1.0f}).release());
            }
        }
        else if (s == "PIRANHA") {
            for (int i = 0; i < n; i++) {
                int x, y; bool ig;
                is >> x >> y >> ig;
                enemies.push_back(
                    (new PiranhaFactory(ig))->createEnemy({x * 1.0f, y * 1.0f}).release()
                );
            }
            continue;
        }
    }

    std::sort(enemies.begin(), enemies.end(), [](auto a, auto b) { return a->getPosition().x < b->getPosition().x; });
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
    // if (pm.doneAction()) {
    //     pm.resetAll();
    // }
    pm.update(delta);
    if (!camChange.empty()) {
        camChange.front().z -= delta;
        if (camChange.front().z <= 0) {
            cam->setTarget({camChange.front().x, camChange.front().y});
            camChange.pop();
        }
    }

    CollisionManager::getInstance().Register(character->shootFireball()); 
    CollisionManager::getInstance().CheckAllCollisions();
    for (int i = 0; i < blocks.size(); i++) {
        blocks[i]->Update(delta, character);
        // Vector2 tmpCam = blocks[i]->changeCam();
        // Vector2 tmpPos = blocks[i]->changePlayerPos(pm);
        // if (tmpPos.x >= 0 && tmpPos.y >= 0) {
        //     character->setGroundLevel(2.0f * GetScreenHeight());
        //     character->setPosition(tmpPos);
        // }
        // if (tmpCam.x >= 0 && tmpCam.y >= 0)
        //     cam->setTarget(tmpCam);
        blocks[i]->changePlayerPos(pm);
        blocks[i]->changeCam(camChange);
    }

    if(character)
        character->update(delta); 

    spawnEnemy();
    for (int i = (int)curEnemies.size() - 1; i >= 0; i--) {
        curEnemies[i]->update(delta);
    }
    
    cam -> update(character); 
}

void Map::spawnEnemy() {
    Vector2 mapSize = getSize();
    float screenW = (float)GetScreenWidth();
    float screenH = (float)GetScreenHeight();
	
    // --- Zoom so whole map fits (optional) ---
    float scaleX = screenW / mapSize.x;
    float scaleY = screenH / mapSize.y;
    float zoom = (std::max(scaleX, scaleY));

    float halfW = screenW * 0.5f / zoom;
    float halfH = screenH * 0.5f / zoom;
    Vector2 target = cam->getCamera().target;

    int i = 0;
    while (i < enemies.size()) {
        Vector2 pos = enemies[i]->getPosition();
        if (pos.x > target.x + halfW)
            break;
        if (pos.y > target.y + halfH || pos.y < target.y - halfH) {
            i++;
            continue;
        }
        curEnemies.push_back(enemies[i]);
        CollisionManager::getInstance().Register(enemies[i]);
        enemies.pop_front();
    }
}

void Map::Draw() const {    
    
    Camera2D camera = cam ->getCamera(); 
    BeginMode2D(camera); 

        DrawTexture(background, 0, 0, WHITE);

        for (int i = 0; i < blocks.size(); i++) {
            blocks[i]->Draw(DrawStat::Zero);
        }
    
        if( character &&  character->hidePlayer()){
            character->render(); 
        }

        for (int i = 0; i < blocks.size(); i++) {
            blocks[i]->Draw(DrawStat::First);
        }
                
        for (int i = 0; i < curEnemies.size(); i++) {
            curEnemies[i]->render();
            // DrawRectangleLines(enemies[i]->getHitbox().x, enemies[i]->getHitbox().y, 
            //                     enemies[i]->getHitbox().width, enemies[i]->getHitbox().height, GREEN);
        }

        if( character &&  !character->hidePlayer()){
            character->render(); 
        }

        for (int i = 0; i < blocks.size(); i++) {
            blocks[i]->Draw(DrawStat::Second);
        }       
    
    EndMode2D(); 
}

void Map::Unload() {
    UnloadTexture(background);
    for (int i = 0; i < blocks.size(); i++)
        delete blocks[i];

    for (int i = 0; i < curEnemies.size(); i++) {
        delete curEnemies[i];
    }

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

    // for (int i = 0; i < enemies.size(); i++) 
    //     CollisionManager::getInstance().Register(enemies[i]);
    pm.setPlayer(character);
}

bool Map::isEnd() {
    return character->getPosition().x >= des;
}