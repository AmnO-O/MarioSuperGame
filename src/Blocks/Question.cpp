#include "Blocks/Question.h"
#include "Character/Character.h"
#include "Resources/StatsManager.h"

Question::Question(Texture2D &tex, std::istream &is) : Block(tex), bounceAni(tex, {0, 0, 0, 0}, 0.25f, 6.0f, 0.2f)
                                                        , ani(tex, false, 0.2f), brokenAni(tex, {0, 0, 0, 0}, 0.25f, 6.0f, 1.0f) {
    int n = 0;
    is >> n;
    for (int i = 0; i < n; i++) {
        int x, y, w, h;
        is >> x >> y >> w >> h;
        ani.addRect({1.0f * x, 1.0f * y, 1.0f * w, 1.0f * h});
        bounceAni.addRect({1.0f * x, 1.0f * y, 1.0f * w, 1.0f * h});
    }

    is >> BrokenRect.x >> BrokenRect.y >> BrokenRect.width >> BrokenRect.height;
    is >> pos.x >> pos.y;

    Vector2 shape = ani.getCurrentShape();
    brokenAni.addRect(BrokenRect);
    brokenAni.setBlockRec({pos.x, pos.y, shape.x, shape.y});
    bounceAni.setBlockRec({pos.x, pos.y, shape.x, shape.y});

    std::string s;
    is >> num;
    is >> s;
    if (s == "COIN") 
        type = QuestionType::COIN;
    else if (s == "POWER") 
        type = QuestionType::POWER;
    else if (s == "STAR") 
        type = QuestionType::STAR;
    else if (s == "NORMAL")
        type = QuestionType::NORMAL;
}

Rectangle Question::getHitbox() const {
    Vector2 position = bounceAni.getPosition();
    return { position.x, position.y, BrokenRect.width, BrokenRect.height };
}

void Question::Update(float delta, Player* player) {
    clearObj();
    for (auto object : objects)
        if (object && object->IsActive()) 
            object->update(delta);

    if (stat == BlockStat::Broken) return; // Don't update if broken

    if (stat == BlockStat::Breaking) {
        brokenAni.Update(delta);
        if (brokenAni.ended())
            stat = BlockStat::Broken;
        return;
    }

    if (stat == BlockStat::Bouncing) {
        bounceAni.Update(delta);
        if (bounceAni.ended())
            stat = BlockStat::Normal;
        return;
    }
    ani.update(delta);
}

void Question::Draw(DrawStat ds) const {
    if (drawStat != ds) return;
    for (auto object : objects)
        if (object && object->IsActive()) 
            object->render();

    if (stat == BlockStat::Breaking || stat == BlockStat::Broken) {
        brokenAni.Draw();
        return;
    }

    if (stat == BlockStat::Bouncing) {
        bounceAni.Draw();
        return;
    }

    if (stat == BlockStat::Normal) {
        ani.Draw(pos);
        return;
    }
}

void Question::adaptCollision(ICollidable* other) {
    if (stat == BlockStat::Normal) {
        Player* Char = dynamic_cast<Player*>(other);
        if (Char) {
            Rectangle body = Char->getHitbox(); // Use character's hitbox
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

            if (dir == BOTTOM) { // Player hit Question from below
                if (stat == BlockStat::Normal)
                    Break(Char);
            }
        }
    }
}

void Question::Break(Player* player) {
    CollisionManager::getInstance().NotifyAbove(this);

    if (creator) delete creator;
    switch (type)
    {
        case QuestionType::COIN:
            creator = new CoinCreator();
            PlaySound(SoundManager::getInstance().coinSound);
            StatsManager::getInstance().addCoins();
            StatsManager::getInstance().addScore(20);
            break;
        
        case QuestionType::POWER:
            if (player->isBig())
            {
                creator = new FireFlowerCreator();
                PlaySound(SoundManager::getInstance().powerUpSound);
            }

            else
            {
                creator = new MushroomCreator();
                PlaySound(SoundManager::getInstance().powerUpSound);
            }

            break;

        case QuestionType::STAR:
            creator = new StarCreator();
            PlaySound(SoundManager::getInstance().powerUpSound);
            break;

        case QuestionType::NORMAL:
            creator = new NormalMushroomCreator();
            break;

        default:
            break;
    }

    if (creator) {
        Vector2 shape = ani.getCurrentShape();
        objects.push_back(creator->create({pos.x, pos.y, shape.x, shape.y}));
        ICollidable* item = dynamic_cast<ICollidable*>(objects[objects.size() - 1]);
        if (item)
            CollisionManager::getInstance().Register(item);
    }
    num--;
    if (num == 0) 
        stat = BlockStat::Breaking;
    else
        stat = BlockStat::Bouncing;
}

void Question::clearObj() {
    objects.erase(
    std::remove_if(objects.begin(), objects.end(),
        [](GameObject* obj) {
            return obj == nullptr || !obj->IsActive();
        }),
    objects.end()
    );
}