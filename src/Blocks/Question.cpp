#include "Blocks/Question.h"
#include "Character/Character.h"

Question::Question(Texture2D &tex, std::istream &is) : Block(tex), bounceAni(tex, {0, 0, 0, 0}, 0.25f, 6.0f, 1.0f), ani(tex, false, 0.2f) {
    int n = 0;
    is >> n;
    for (int i = 0; i < n; i++) {
        int x, y, w, h;
        is >> x >> y >> w >> h;
        ani.addRect({1.0f * x, 1.0f * y, 1.0f * w, 1.0f * h});
    }

    is >> BrokenRect.x >> BrokenRect.y >> BrokenRect.width >> BrokenRect.height;
    is >> pos.x >> pos.y;

    Vector2 shape = ani.getCurrentShape();
    bounceAni.addRect(BrokenRect);
    bounceAni.setBlockRec({pos.x, pos.y, shape.x, shape.y});

    std::string s;
    is >> num;
    is >> s;
    if (s == "COIN") 
        type = QuestionType::COIN;
    else if (s == "BIG") 
        type = QuestionType::POWER;
    else if (s == "STAR") 
        type = QuestionType::STAR;
}

Rectangle Question::getHitbox() const {
    Vector2 position = bounceAni.getPosition();
    return { position.x, position.y, BrokenRect.width, BrokenRect.height };
}

void Question::Update(float delta) {
    if (object && object->IsActive()) object->update(delta);

    if (stat == BlockStat::Broken) return; // Don't update if broken

    if (stat == BlockStat::Bouncing) {
        bounceAni.Update(delta);
        if (bounceAni.ended()) {
            stat = BlockStat::Broken;
        }
        return;
    }
    ani.update(delta);
}

void Question::Draw(DrawStat ds) const {
    if (drawStat != ds) return;
    if (object && object->IsActive()) object->render();

    if (stat == BlockStat::Bouncing || stat == BlockStat::Broken) {
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

    switch (type)
    {
        case QuestionType::COIN:
            creator = new CoinCreator();
            PlaySound(SoundManager::getInstance().coinSound);
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

        default:
            break;
    }

    if (creator) {
        Vector2 shape = ani.getCurrentShape();
        object = creator->create({pos.x, pos.y, shape.x, shape.y});
        ICollidable* item = dynamic_cast<ICollidable*>(object);
        if (item)
            CollisionManager::getInstance().Register(item);
    }
    stat = BlockStat::Bouncing;
}