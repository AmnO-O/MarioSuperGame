#pragma once 
#include <fstream>
#include "raylib.h"
#include "Animation.h"
#include "Global.h"
#include "Exceptions.h"
#include "CharacterState.h"
#include "PlayerMovement.h"
#include "Fireball.h"
#include "Observer/ICollidable.h"


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
    Vector2 getVelocity() const {return velocity;}

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



class Player : public ICollidable, public Character{
private: 
    PlayerMovement* movement; 
    IShapeState *Sstate; 
    IMoveState *Mstate; 

    CharacterType type; 
	std::map<std::string, std::unique_ptr<AnimationManager>> animations; 
    std::vector<Fireball*> fireballs;
	AnimationManager *activeAnimation;

    void updateHitbox(); 
    void readRectAnimation(const std::string filePath, Texture2D &sheet); 
    std::string getShape_Action() const; 
    void cleanFireballs(); 
    void updateShape(); 
    void setUp(); 
    void adaptChangePosition(); 
    void animationTransform(); 
    void switchPlayer(); 
public: 
    Player(CharacterType type, Vector2 pos); 
    Player(CharacterType type, float cordX, float groundLevel); 

    Vector2 getPosition() const {return movement->getPosition(); }
    Rectangle getHitbox() const override {return hitbox; }
    
    bool isBig() const { return Sstate->canBreakBrick();}
    bool isInvincible() const {return Sstate->isInvincible();}

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