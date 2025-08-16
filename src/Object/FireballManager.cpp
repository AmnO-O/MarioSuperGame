#include "Object/FireballManager.h"
#include "Resources/SoundManager.h"
#include "Observer/Observer.h"
#include <algorithm>
#include <iostream>

FireballManager::FireballManager() {
    fireballs.clear();
}

FireballManager::~FireballManager() {
    for(auto &fb : fireballs){
        delete fb;
        fb = nullptr;
    }
}

void FireballManager::cleanFireballs() {
    fireballs.erase(
        std::remove_if(fireballs.begin(), fireballs.end(),
            [](const auto &fb) { return !fb->isActive(); }),
        fireballs.end()
    );
}

void FireballManager::update(float deltaTime) {
    cleanFireballs();
    for (auto& fb : fireballs)
        fb->update(deltaTime);
}

Fireball* FireballManager::shootFireball(Vector2 playerPosition, bool isFacingRight) {
    playerPosition.x += (isFacingRight ? 15 : -5);
    playerPosition.y += 5;

    Fireball* fireball = new Fireball(playerPosition, isFacingRight);
    fireball->setGroundLevel(INFINITY);
    fireballs.emplace_back(fireball);
    PlaySound(SoundManager::getInstance().fireballSound);

    return fireball;
}

void FireballManager::render() {
    for(auto &fb : fireballs){
        fb->render();
    }
}

void FireballManager::printData(std::ostream &fout) const {
    fout << fireballs.size() << '\n';
    for (const auto& fb : fireballs) {
        fb->printData(fout);
    }
}

void FireballManager::loadData(std::istream &fin) {
    int size;
    fin >> size;
    fireballs.clear();
    for (int i = 0; i < size; ++i) {
        Fireball* fb = new Fireball({0, 0}, true);
        fb->loadData(fin);
        fireballs.push_back(fb);
        CollisionManager::getInstance().Register(fb);
    }
}
