#pragma once
#include "Fireball.h"
#include "Resources/SoundManager.h"
#include <algorithm>

class FireballManager{
    std::vector<Fireball*> fireballs;
    void cleanFireballs(){
        fireballs.erase(
            std::remove_if(fireballs.begin(), fireballs.end(), [](const auto &fb) { return !fb->isActive(); }),
            fireballs.end()
        );
    }
public: 
    FireballManager(){
        fireballs.clear(); 
    }

    void update(float deltaTime){
        cleanFireballs();

	    for (auto& fb : fireballs)
		    fb->update(deltaTime);
    }

    Fireball* shootFireball(Vector2 playerPosition, bool isFacingRight){
        Fireball *fireball = nullptr; 
		
        playerPosition.x += (isFacingRight ? 15 : -5);
		playerPosition.y += 5;

        fireball = new Fireball(playerPosition, isFacingRight); 
		fireball->setGroundLevel(2.0f * GetScreenHeight()); 
        fireballs.emplace_back(fireball);
        PlaySound(SoundManager::getInstance().fireballSound);

        return fireball; 
    }

    void render(){
        for(auto &fb : fireballs){
            fb -> render(); 
        }
    }

    ~FireballManager() {
        for(auto &fb : fireballs){
            delete fb;
            fb = nullptr; 
        }
    }; 
}; 