#include "Blocks/Flag.h"
#include "Resources/StatsManager.h"
#include "Resources/SoundManager.h"
#include "Resources/Timer.h"
#include "Resources/StatsManager.h"

Flag::Flag(Texture2D &tex, std::istream &is, float time) : Block(tex), time(time), animationClimbFlag(nullptr) {
    // drawStat = DrawStat::Zero;
    is >> head.x >> head.y >> head.width >> head.height;
    is >> body.x >> body.y >> body.width >> body.height;
    is >> pos.x >> pos.y;
    is >> height;
    // is >> tp.x >> tp.y;
    if (height < head.height)
        throw ResourceException("Flag height < Flag Head!");
}

Rectangle Flag::getHitbox() const {   
    return {pos.x + head.width - body.width, pos.y, body.width, 1.0f * height};
}

void Flag::Draw(DrawStat ds) const {
    if (drawStat != ds) return;    
    for (int i = 0; i < (int)height / (int)body.height; i++) {
        DrawTextureRec(tex, body, {pos.x + head.width - body.width, pos.y + body.height * i}, WHITE);
    }
    Rectangle rec = body;
    rec.height = height - body.height * ((int)height / (int)body.height);
    DrawTextureRec(tex, rec, {pos.x + head.width - body.width, pos.y + height - rec.height}, WHITE);

    DrawTextureRec(tex, head, {pos.x, pos.y + frametime / time * (height - head.height)}, WHITE);

}

void Flag::Update(float deltaTime, Player* player) { 
    if(animationClimbFlag != nullptr)
        animationClimbFlag->update(deltaTime); 

    if (hasClimb){
        frametime += deltaTime;

        if (frametime > time) {
            frametime = time;
            hasClimb = false;
        }

        return;
    }
    
}

// Vector2 Flag::changeCam() {
//     return {-1.0f, -1.0f};
// }
// Vector2 Flag::changePlayerPos() {
//     if (hasClimb && animationClimbFlag->doneAction())
//         return tp;
//     return {-1.0f, -1.0f};
// }

void Flag::adaptCollision(ICollidable* other) {
    Player* player = dynamic_cast<Player*>(other);

    if (player) {
        Rectangle body = player->getHitbox(); 
        Rectangle hitbox = getHitbox();
        // Check overlap
        float left = (body.x + body.width) - hitbox.x;
        float right = (hitbox.x + hitbox.width) - body.x;
        float top = (body.y + body.height) - hitbox.y;
        float bottom = (hitbox.y + hitbox.height) - body.y;
        //if (left <= 0 || right <= 0 || top <= 0 || bottom <= 0) return;

        // Find minimal penetration
        float minPen = left;
        enum Dir { LEFT, RIGHT, TOP, BOTTOM } dir = LEFT;
        if (right < minPen) { minPen = right; dir = RIGHT; }
        if (top < minPen) { minPen = top; dir = TOP; }
        if (bottom < minPen) { minPen = bottom; dir = BOTTOM; }

        float collision_height = hitbox.y + hitbox.height - body.y;
        int extra_points = static_cast<int>(collision_height / 16) * 100;
        StatsManager::getInstance().addScore(extra_points);

        if (dir == LEFT) { 
            hasClimb = true;
            animationClimbFlag = std::make_unique<PlayerActionManager>(player); 
            animationClimbFlag->addAction(std::make_unique<ClimbAction>(hitbox.y + hitbox.height - player->getShape().y, time + 0.5f));
            animationClimbFlag->addAction(std::make_unique<SetPositionAction>(Vector2({hitbox.x + hitbox.width, hitbox.y + hitbox.height - player->getShape().y}), false, 0.5f));
            animationClimbFlag->addAction(std::make_unique<JumpAction>(166.0f, -200.0f));
            PlaySound(SoundManager::getInstance().flagpoleSound);
            StatsManager::getInstance().time_taken = 300.0f - Timer::getInstance().remaining;
        }
    }
}

void Flag::save(std::ostream &os) {
    os << frametime << " " << hasClimb << "\n";
    // animationClimbFlag->save(os);
}