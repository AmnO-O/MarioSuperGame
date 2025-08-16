#ifndef INVISIBLE_H
#define INVISIBLE_H

#include "raylib.h"
#include "Question.h"
#include "iostream"

class Invisible : public Question {
private:
    
public:
    Invisible(Texture2D &tex, std::istream &is) : Question(tex, is) {}
    Rectangle getHitbox() const override {
        Rectangle rec = Question::getHitbox();
        if (stat == BlockStat::Normal)
            return {rec.x, rec.y, 0, 0};
        else
            return rec;
    }
    void Update(float delta, Player* player) override {
        Question::Update(delta, player);

        // If already revealed, behave like a normal Question
        if (stat != BlockStat::Normal) return;

        // --- Special check: did player hit from below? ---
        Rectangle playerBox = player->getHitbox();
        Rectangle blockBox  = Question::getHitbox();

        // Only check collision if the player’s head is inside block’s bottom area
        bool withinX = playerBox.x + playerBox.width  > blockBox.x &&
                       playerBox.x < blockBox.x + blockBox.width;

        bool hitFromBelow = (playerBox.y <= blockBox.y + blockBox.height &&
                             playerBox.y + playerBox.height > blockBox.y + blockBox.height - 4);

            // std::cout << player->getVelocity().y << "\n";
        if (withinX && hitFromBelow && player->getVelocity().y < 0) {
            // Reveal and break the invisible block
            Break(player);
        }
    }
    ~Invisible() override {}
};

#endif
