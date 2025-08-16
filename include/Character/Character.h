#pragma once 
#include <fstream>
#include "raylib.h"
#include "Animation/Animation.h"
#include "Global.h"
#include "../Exceptions.h"
#include "CharacterState.h"
#include "PlayerMovement.h"
#include "Object/FireballManager.h"
#include "Observer/ICollidable.h"
#include "PlayerAction.h"
#include "Resources/SoundManager.h"
#include <iostream>


class Character{
protected:
    Vector2 position; 
    Vector2 velocity; 
    bool dead = false; 
    AnimationManager *activeAnimation = nullptr; 
    Rectangle hitbox; 
    float groundLevel; 

    virtual void updateHitbox(){
        if(activeAnimation == nullptr)
            throw GameException("Movement ptr activeAnimation is null in Character::updateHitbox");

        auto [w, h] = activeAnimation->getCurrentShape();
        hitbox = {position.x, position.y, w, h};
    }

    virtual void readRectAnimation(const std::string filePath, Texture2D &sheet){}
public: 
    Character(): position({0, 0}), velocity({0, 0}), dead(false), activeAnimation(nullptr), groundLevel(10000.0f){
        hitbox = {0, 0, 16, 16}; 
    }
    // Getters
    Rectangle getHitbox() const {return hitbox; }
    Vector2 getPosition() const {return position;}
    virtual Vector2 getVelocity() const {return velocity;}

    // Setters
    virtual void setPosition(const Vector2 &pos) {this->position = pos; updateHitbox();}
    virtual void setGroundLevel(float groundLevel){this->groundLevel = groundLevel; }
    virtual void setOnGround(){
        if(activeAnimation == nullptr)
            throw GameException("Movement ptr activeAnimation is null in Character::setOnGround");

        auto [w, h] = activeAnimation->getCurrentShape();
        position.y = groundLevel - h; 
        velocity.y = 0.0f; 
        updateHitbox();
    }

    /// Other stuff
    virtual void update(float deltaTime){
        if(activeAnimation)
		    activeAnimation->update(deltaTime);
        
        position.x += velocity.x * deltaTime;
	    position.y += velocity.y * deltaTime;
    }

    virtual void render(){
        if(activeAnimation)
		    activeAnimation->render(position, false);
    }
    virtual ~Character() {}; 
}; 

class BlinkCounter {
private:
    float currentTime    = 0.0f;  
    float interval       = 0.1f;  
    float totalDuration  = 3.0f;  
    bool  active         = false; 

public:
    BlinkCounter(float interval = 0.1f, float totalDuration = 10.0f)
      : interval(interval), totalDuration(totalDuration) {}

    void reset() {
        currentTime = 0.0f;
        active = true;
    }

    bool update(float deltaTime) {
        if (!active) return true; 

        currentTime += deltaTime;
        if (currentTime >= totalDuration) {
            active = false;
            return true;
        }

        int phase = static_cast<int>(currentTime / interval);
        return (phase % 2) == 0; 
    }

    bool isActive() const { return active; }
};



class Player : public ICollidable, public Character{
private: 
    friend class PlayerActionManager; 

private: 

    PlayerMovement* movement; 
    IShapeState *Sstate; 
    IMoveState *Mstate; 
	std::map<std::string, std::unique_ptr<AnimationManager>> animations; 
    
    FireballManager fireballs;

	AnimationManager *activeAnimation;

    BlinkCounter blink; 
    CharacterType type; 

    bool shrinkOnHit = false; 
    bool showPlayer = false; 


    void updateHitbox(); 
    void readRectAnimation(const std::string filePath, Texture2D &sheet); 
    std::string getShape_Action() const; 

    void updateShape(); 
    void setUp(); 
    void adaptChangePosition(); 
    void animationTransform(); 
    void switchPlayer(); 
    void adapt_collision_with_enimies(ICollidable* other); 
    void triggerDeath(); 
public: 
    Player(CharacterType type, Vector2 pos); 
    Player(CharacterType type, float cordX, float groundLevel); 

    void loadData(std::istream &fin); 
    void printData(std::ostream &fout); 

    void changeMstate(IMoveState *Mstate_){
        if(Mstate_ && Mstate->getMoveState() != Mstate_->getMoveState()){
            delete Mstate; 
            Mstate = Mstate_;    
            
            updateShape(); 
            updateHitbox(); 

            return; 
        }

        if(Mstate_) 
            delete Mstate_; 
    }

    void changeSstate(IShapeState *Sstate_){
        if(Sstate->getShapeState() != Sstate_->getShapeState()){
            delete Sstate; 
            Sstate = Sstate_;    
            updateShape(); 
            updateHitbox(); 
            return; 
        }

        delete Sstate_; 
    }

    Vector2 getPosition() const {return movement->getPosition(); }
    Rectangle getHitbox() const override {return hitbox; }
    Vector2 getShape() const{return Vector2({hitbox.width, hitbox.height});}
    Vector2 getVelocity() const override {return movement->getVelocity();}

    bool isBig() const { return Sstate->canBreakBrick();}
    bool isInvincible() const {return Sstate->isInvincible();}
    bool canShootFire() const {return Sstate->canShootFire();}
    bool isDead() const {return Mstate->isDead(); }
    bool isRecovery() const {return blink.isActive() || shrinkOnHit; }
    bool IsActive() const override{return Mstate->isDead() == false;}
    bool hidePlayer() const{return movement->isLocked(); }
    bool isLocked() const{return movement->isLocked(); }
    
    // setter 
    void setPosition(const Vector2 &pos); 
    void setOnGround(); 

    Fireball* shootFireball();
    void adaptCollision(ICollidable* other) override;
    void powerUp(PowerUpType type); 
    void setGroundLevel(float groundLevel); 
    void update(float deltaTime); 
    void render(); 

    ~Player(); 
}; 
