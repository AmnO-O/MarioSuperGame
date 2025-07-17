#include "Character/Character.h"
#include <fstream>
#include "Exceptions.h"

Character::Character(CharacterType t, Vector2 pos):
    type(t), position(pos), velocity({0, 0}), 
    Sstate(new SmallState()), Mstate(new StandState()), facingRight(true){
    
    if(type == CharacterType::MARIO){
        stats = std::make_unique<MarioStats>(); 

    }else if(type == CharacterType::LUIGI){
        stats = std::make_unique<LuigiStats>(); 

    }
}


void Character::readRectAnimation(const std::string filename) {
	std::ifstream fin(filename); 

	if (!fin.is_open()) 
		throw ResourceException("Can't load " + filename); 

    

	fin.close(); 
}




void Character::updateHixbox(){
    hitbox = {position.x, position.y, 16, 16}; 
}

void Character::transformToTransformed() {
    if(Sstate && Sstate->getShapeState() != "TRANSFORMED"){
        delete Sstate; 
        Sstate = nullptr; 
    }

    if(Sstate == nullptr) 
        Sstate = new TransformedState(); 
}

void Character::transformToFire() {
    if(Sstate && Sstate->getShapeState() != "FIRE"){
        delete Sstate; 
        Sstate = nullptr; 
    }

    if(Sstate == nullptr) 
        Sstate = new FireState();
}

void Character::update(float deltaTime){
    
}

void Character::render(){

}

