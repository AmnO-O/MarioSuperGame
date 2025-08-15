#include "States/SubMenu.h"
#include "States/MainMenu.h"
#include "States/LevelMenu.h"
#include "States/World.h"

SubMenu::SubMenu()
  : mario_button("MARIO GAME", {(GetScreenWidth() * 1.f - 350.0f) / 2.0f, 400, 350, 60}, WHITE, RED, [&]() { 
        StateManager::getInstance().pushState(std::make_unique<LevelMenu>(true));  
    }),
    luigi_button("LUIGI GAME", {(GetScreenWidth() * 1.f - 350.0f) / 2.0f, 533, 350, 60}, WHITE, RED, [&]() { 
        StateManager::getInstance().pushState(std::make_unique<LevelMenu>(false));
    }), 
    return_button("assets/images/turn_back_white.png", {25, 27, 100, 100}, [&]() {
        StateManager::getInstance().pushState(std::make_unique<MainMenu>());
    }),
    title("CHOOSE YOUR CHARACTER") 
{
    sub_background = LoadTexture("assets/images/sub_menu_background.png");
    return_button_state = LoadTexture("assets/images/turn_back_red.png");
    titleFont = LoadFont("assets/fonts/SuperMarioBros.ttf");

    playerPreviews.clear();

    int screenWidth = GetScreenWidth();
    int numPlayers = 2;
    int previewWidth = 180;
    int previewHeight = 240;
    int spacing = 100;

    int totalWidth = (numPlayers * previewWidth) + ((numPlayers - 1) * spacing);

    float startX = (screenWidth * 1.0f - totalWidth * 1.0f) / 2.0f;

    for (int i = 0; i < numPlayers; i++) {
        Rectangle preview = {
            startX + i * (previewWidth + spacing) * 1.0f, // Vị trí x của mỗi ô
            290.0f,
            (float)previewWidth,
            (float)previewHeight
        };
        playerPreviews.push_back(preview);
    }

    select_button.setUp("SELECT", { (GetScreenWidth() * 1.f - 350.0f) / 2.0f, 600, 350, 60 }, WHITE, RED, [&]() {
        if (selectedPlayer < 4) {
            StateManager::getInstance().pushState(std::make_unique<LevelMenu>(selectedPlayer == 0));
        }
    });

    playerTextures.push_back(LoadTexture("assets/images/mario_display.png"));
    playerTextures.push_back(LoadTexture("assets/images/luigi_display.png"));
    playerTextures.push_back(LoadTexture("assets/images/peach.png"));
    playerTextures.push_back(LoadTexture("assets/images/toad.png"));
}

SubMenu::~SubMenu()
{
    UnloadFont(titleFont);
    UnloadTexture(sub_background);
    UnloadTexture(return_button_state);

    for(auto & texture : playerTextures) {
        UnloadTexture(texture);
    }
}

void SubMenu::update(float deltaTime) 
{
    return_button.update(deltaTime);

    Vector2 mousePos = GetMousePosition();

    if(select_button.isCliked() || IsKeyPressed(KEY_ENTER)) {
        if (selectedPlayer == 0) {
            mario_button.activate();
        }else{
            luigi_button.activate();
        }
    }

    if(IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)){
        selectedPlayer = (selectedPlayer + 1) % (int)playerPreviews.size();
    } else if(IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)){
        selectedPlayer = (selectedPlayer - 1 + playerPreviews.size()) % (int)playerPreviews.size();
    }

    for (int i = 0; i < playerPreviews.size(); i++) {
        if (CheckCollisionPointRec(mousePos, playerPreviews[i])) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                selectedPlayer = i;
            }
        }
    }

    bool isOn = false; 

    for (int i = 0; i < playerPreviews.size(); i++) {
        if (CheckCollisionPointRec(mousePos, playerPreviews[i])) {
            curHovered = i; 
            isOn = true; 
        }
    }

    if(isOn == false){
        curHovered = -1; 
    }

}

void SubMenu::render() 
{
    DrawTexture(sub_background, 0, 0, WHITE);

    // mario_button.render();
    // luigi_button.render();
    return_button.render();
    select_button.render();

    bool isHovered = CheckCollisionPointRec(GetMousePosition(), return_button.getBounds());
    if (isHovered)
        DrawTexture(return_button_state, 25, 27, WHITE);

    DrawTextEx(titleFont, title.c_str(), {324, 79}, 50, 2, BLACK);



    std::vector<std::string> playerNames = { "MARIO", "LUIGI", "PEACH", "TOAD" };
    std::vector<Color> playerColors = { RED, GREEN, PINK, BLUE };

    for (int i = 0; i < playerPreviews.size(); i++) {
        Rectangle preview = playerPreviews[i];
        Color playerColor = (i == selectedPlayer) ? YELLOW : (i == curHovered ? Fade(GREEN, 0.8f) : WHITE);

        DrawRectangleRec(preview, {50, 50, 50, 220});
        if (i == curHovered || i == selectedPlayer) {
            DrawRectangle((int)preview.x + 5, (int)preview.y + 5, (int)preview.width, (int)preview.height, {0, 0, 0, 50});
        }

        DrawRectangleLinesEx(preview, 5, playerColor);
        
        if(i < 2){
            float scale = (i == curHovered || i == selectedPlayer) ? 1.6f : 1.4f;
            Rectangle sourceRec = { 0, 0, (float)playerTextures[i].width, (float)playerTextures[i].height };
            Rectangle destRec = {
                preview.x + preview.width / 2 - (80 * scale) / 2.0f,
                preview.y + 40.0f,
                80 * scale,
                80 * scale
            };
            Vector2 origin = { 0, 0 };
            DrawTexturePro(playerTextures[i], sourceRec, destRec, origin, 0.0f, WHITE);
        }else{
            // Vẽ vòng tròn đại diện nhân vật
            float circleScale = (i == curHovered || i == selectedPlayer) ? 1.2f : 1.0f;
            DrawCircle((int)preview.x + preview.width / 2,
                    (int)preview.y + 90, 40 * circleScale, playerColors[i]);
        }

        Vector2 textSize = MeasureTextEx(titleFont, playerNames[i].c_str(), 24, 2);
        DrawTextEx(titleFont, playerNames[i].c_str(),
                  { preview.x + (preview.width - textSize.x) / 2,
                    preview.y + preview.height - 40 }, 24, 2, playerColor);
    }
}