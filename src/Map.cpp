#include "Map.hpp"
#include <fstream>

void Map::input(std::istream &is) {
    is >> space;
}

Map::Map(const std::string& folderPath) {
    std::string path = folderPath + "/map.png";
    background = LoadTexture(path.c_str());
    path = folderPath + "/info.txt";
    std::ifstream fin;
    fin.open(path);
    if (!fin.is_open())
        throw ResourceException("Can't load map info");
    input(fin);

    // //Floor
    // int n;
    // fin >> n;
    // for (int i = 0; i < n; i++) {
    //     int x, y, num;
    //     fin >> x >> y >> num;
    //     blocks.push_back(new Floor(blockTex, {x * scale, y * scale}, num));
    // }
    // //Brick
    // fin >> n;
    // for (int i = 0; i < n; i++) {
    //     int x, y;
    //     fin >> x >> y;
    //     blocks.push_back(new Brick(blockTex, {x * scale, y * scale}));
    // }
    fin.close();
}

void Map::Update(float delta) {
    // for (int i = 0; i < blocks.size(); i++)
    //     blocks[i]->Update();
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

    // for (int i = 0; i < blocks.size(); i++) {
    //     blocks[i]->Draw(Camera, DrawStat::First);
    // }
    
    // for (int i = 0; i < blocks.size(); i++) {
    //     blocks[i]->Draw(Camera, DrawStat::Second);
    // }

}

void Map::Unload() {
    UnloadTexture(background);
    // for (int i = 0; i < blocks.size(); i++)
    //     delete blocks[i];
}
