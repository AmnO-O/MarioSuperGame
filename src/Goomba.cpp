#include "Character/Goomba.h"
#include "Character/Character.h"
#include "Character/Character.h"
#include "Character/Global.h"
#include <cmath>

Goomba::Goomba(Vector2 pos) : Enemy(pos) {
    Texture2D& tex = Images::textures["enemies_sprites.png"];
    readRectAnimation("assets/animation/goomba.txt", tex);
    updateHitbox();
}

void Goomba::update(float deltaTime) {
    if (dead) return;

    velocity.y += 980 * deltaTime;
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;

    updateHitbox();
    if (activeAnimation)
        activeAnimation->update(deltaTime);
}

void Goomba::render() {
    if (!dead && activeAnimation)
        activeAnimation->render(position);
}

void Goomba::adaptCollision(ICollidable* other) {
    Player* player = dynamic_cast<Player*>(other);
    if (player && player->getVelocity().y > 0 && player->getPosition().y < position.y) {
        kill();
        velocity = { 0, 0 };
    }
}
