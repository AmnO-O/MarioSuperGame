#include "Blocks/Lift.h"
#include "Resources/SoundManager.h"

Lift::Lift(Texture2D &tex, std::istream &is) : Block(tex) {
    is >> srcRect.x >> srcRect.y >> srcRect.width >> srcRect.height;
    is >> width;
    is >> pos.x >> pos.y;
    is >> start.x >> start.y;
    is >> des.x >> des.y;
    is >> canBack;
    if (!canBack) {
        bool inverse;
        is >> inverse;
        if (inverse) {
            velocity.x *= -1;
            velocity.y *= -1;
        }
    }
    // if (width < srcRect.width)
    //     throw ResourceException("Lift width < Lift Rec!");
    
}

Rectangle Lift::getHitbox() const {   
    return {pos.x, pos.y, 1.0f * width, srcRect.height};
}

void Lift::Draw(DrawStat ds) const {
    if (drawStat != ds) return;
    for (int i = 0; i < (width) / (int)srcRect.width; i++) {
        DrawTextureRec(tex, srcRect, {pos.x + i * srcRect.width, pos.y}, WHITE);
    }
    Rectangle rec = srcRect;
    rec.width = width - srcRect.width * ((width) / (int)srcRect.width);
    DrawTextureRec(tex, rec, {pos.x + width - rec.width, pos.y}, WHITE);
}

void Lift::Update(float deltaTime, Player* player) { 
    Rectangle hitbox = getHitbox();
    Vector2 distance = {velocity.x * deltaTime, velocity.y * deltaTime};   
    
    pos.x += distance.x;
    pos.y += distance.y;


    //// if remove the !canBack, the lift move in horizontal will be more soomt
    if (pos.x > des.x) {    
        if(!canBack)
            pos.x = start.x;
        else {
            velocity.x *= -1;
            pos.x = des.x;
        }
        distance.x = 0;
    }

    if (pos.x < start.x) {        
        if(!canBack)
            pos.x = des.x;
        else {
            velocity.x *= -1;
            pos.x = start.x;
        }
        distance.x = 0;
    }

    if (pos.y > des.y) {
        if(!canBack)
            pos.y = start.y;
        else {
            velocity.y *= -1;
            pos.y = des.y;
        }
        distance.y = 0;
    }

    if (pos.y < start.y) {
        if(!canBack)
            pos.y = des.y;
        else {
            velocity.y *= -1;
            pos.y = start.y;
        }
        distance.y = 0;
    }

    // std::cout << distance.x << ' ' << distance.y << '\n'; 

    if (player) {
        Rectangle playerBox = player->getHitbox();
        bool onTop =
            playerBox.y + playerBox.height <= hitbox.y + 2.0f && // Feet at top or slightly above
            playerBox.y + playerBox.height >= hitbox.y && // Within a small tolerance
            playerBox.x + playerBox.width > hitbox.x &&          // Horizontal overlap
            playerBox.x < hitbox.x + hitbox.width;

        if (onTop && player->getVelocity().x == 0.0f && player->getVelocity().y == 0.0f) {
            // Move player together with lift
            Vector2 playerPos = player->getPosition();
            playerPos.x += distance.x;
            playerPos.y += distance.y;
            player->setPosition(playerPos);

            // Update ground level so gravity stops pulling them
            player->setGroundLevel(pos.y);
            player->setOnGround(); 
        }
    }
}

void Lift::save(std::ostream &os) {
    os << pos.x << " " << pos.y << " " << velocity.x << " " << velocity.y << "\n";
}

void Lift::load(std::istream &is) {
    is >> pos.x >> pos.y >> velocity.x >> velocity.y;
}