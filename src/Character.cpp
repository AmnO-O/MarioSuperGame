#include "Character/Character.h"
#include <iostream>

Character::Character(CharacterType t, Vector2 pos):
    type(t), 
    Sstate(new SmallState()), Mstate(new StandState()), activeAnimation(nullptr){
    
    if(type == CharacterType::MARIO){
		movement = new PlayerMovement(pos, {0, 0}, std::make_unique<MarioStats>()); 

		Texture& mario = Images::textures["mario.png"];

		if(mario.id == 0)
			throw GameException("Can't load image of mario.png");
		readRectAnimation("assets/animation/mario.txt");

	}else if(type == CharacterType::LUIGI){
		movement = new PlayerMovement(pos, {0, 0}, std::make_unique<LuigiStats>()); 
		readRectAnimation("assets/animation/luigi.txt");
    }
}

std::string Character::getShape_Action() const{
	return Sstate->getShapeState() + "_" + Mstate->getMoveState(); 
}

void Character::readRectAnimation(const std::string filename) {
	std::ifstream fin(filename); 

	if (!fin.is_open()) 
		throw ResourceException("Can't load " + filename); 


	for (int id = 0; id < 3; id++) {
		std::string shape = "";
		fin >> shape;

		if (shape == "SMALL") {
			shape += "_";

			std::string action = "";

			for (int i = 0; i < 4; i++) {
				int numAnimation;
				fin >> action >> numAnimation;

				std::string key = shape + action;
				animations[key] = std::make_unique<AnimationManager>(Images::textures["mario.png"], 0);

				for (int j = 0; j < numAnimation; j++) {
					float x, y, width, height;
					fin >> x >> y >> width >> height;
					animations[key]->addRect(Rectangle({ x, y, width, height }));
				}
			}
		}

		if (shape == "BIG") {
			shape += "_";
			std::string action = "";

			for (int i = 0; i < 5; i++) {
				int numAnimation;
				fin >> action >> numAnimation;

				std::string key = shape + action;
				animations[key] = std::make_unique<AnimationManager>(Images::textures["mario.png"], 0);

				for (int j = 0; j < numAnimation; j++) {
					float x, y, width, height;
					fin >> x >> y >> width >> height;
					animations[key]->addRect(Rectangle({ x, y, width, height }));
				}
			}
		}

		if (shape == "FIRE") {
			shape += "_";

		}

	}

	updateHitbox(); 

	fin.close(); 
}

void Character::updateHitbox(){
	if(movement == nullptr)
		throw GameException("Movement is null in Character::updateHitbox"); 

	Vector2 current = movement -> getPosition();

    hitbox = {current.x, current.y, 16, 16}; 
}

void Character::update(float deltaTime){
	if(movement == nullptr)
		throw GameException("Movement is null in Character::update"); 

	movement -> update(deltaTime, Sstate, Mstate); 

	std::string animationKey = getShape_Action(); 

	if(activeAnimation != animations[animationKey].get())
		activeAnimation = animations[animationKey].get(); 

	if(activeAnimation == nullptr)
		throw GameException("Active animation is null in Character::update");

	if(activeAnimation)
		activeAnimation->update(deltaTime); 

	updateHitbox(); 
}

void Character::render(){
	if(activeAnimation) 
		activeAnimation->render(movement->getPosition(), movement->isFacingRight() == false);
}

Character::~Character() {
	delete Sstate; 
	delete Mstate; 
	delete movement; 
	Images::unloadAllTextures();
}

