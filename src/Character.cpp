#include "Character/Character.h"
#include <iostream>
#include <cassert>


void Character::setUp(){
	Sstate = new FireState(); 
	Mstate = new StandState(); 
	activeAnimation = nullptr; 
}

Character::Character(CharacterType t, Vector2 pos):
    type(t){
	setUp(); 

    if(type == CharacterType::MARIO){
		Texture& mario = Images::textures["mario.png"];

		if(mario.id == 0)
			throw GameException("Can't load image of mario.png");

		readRectAnimation("assets/animation/mario.txt", mario);
		updateShape(); 
		groundLevel = pos.y + activeAnimation->getCurrentShape().y; 

		movement = new PlayerMovement(pos, {0, 0}, std::make_unique<MarioStats>()); 
		movement->setGroundLevel(groundLevel); 
		movement->setShape(activeAnimation->getCurrentShape()); 


	}else if(type == CharacterType::LUIGI){
		Texture& luigi = Images::textures["luigi.png"];

		if(luigi.id == 0)
			throw GameException("Can't load image of luigi.png");

		readRectAnimation("assets/animation/luigi.txt", luigi);
		updateShape(); 
		groundLevel = pos.y + activeAnimation->getCurrentShape().y; 

		movement = new PlayerMovement(pos, {0, 0}, std::make_unique<LuigiStats>()); 
		movement->setGroundLevel(groundLevel); 
		movement->setShape(activeAnimation->getCurrentShape());
    }

	updateHitbox(); 
}

Character::Character(CharacterType t,  float cordX, float groundLevel):
    type(t){

	setUp(); 

    if(type == CharacterType::MARIO){
		Texture& mario = Images::textures["mario.png"];

		if(mario.id == 0)
			throw GameException("Can't load image of mario.png");

		readRectAnimation("assets/animation/mario.txt", mario);
		updateShape(); 
		Vector2 pos = {cordX, groundLevel - activeAnimation->getCurrentShape().y };

		movement = new PlayerMovement(pos, {0, 0}, std::make_unique<MarioStats>()); 
		movement->setGroundLevel(groundLevel); 

	}else if(type == CharacterType::LUIGI){
		Texture& luigi = Images::textures["luigi.png"];

		if(luigi.id == 0)
			throw GameException("Can't load image of luigi.png");

		readRectAnimation("assets/animation/luigi.txt", luigi);
		updateShape(); 
		Vector2 pos = {cordX, groundLevel - activeAnimation->getCurrentShape().y };

		movement = new PlayerMovement(pos, {0, 0}, std::make_unique<LuigiStats>()); 
		movement->setGroundLevel(groundLevel); 
    }

	updateHitbox(); 
}

std::string Character::getShape_Action() const{
	assert(Mstate != nullptr); 
	assert(Sstate != nullptr); 

	return Sstate->getShapeState() + "_" + Mstate->getMoveState(); 
}

void Character::updateShape(){
	std::string animationKey = getShape_Action(); 

	if(activeAnimation != animations[animationKey].get()){
		activeAnimation = animations[animationKey].get(); 
	}

	if(activeAnimation == nullptr)
		throw GameException("Active animation is null in Character::updateShape " + animationKey);
}

void Character::updateHitbox(){	
	if(movement == nullptr || activeAnimation == nullptr)
		throw GameException("Movement ptr activeAnimation is null in Character::updateHitbox"); 

	auto [w, h] = activeAnimation->getCurrentShape(); 	
	movement->setShape(Vector2{w, h}); 

	Vector2 current = movement -> getPosition(); 
	hitbox = {current.x, current.y, w, h}; 	
}

void Character::readRectAnimation(const std::string filename, Texture2D &sheet) {
	std::ifstream fin(filename); 

	if (!fin.is_open()) 
		throw ResourceException("Can't load " + filename); 


	for (int id = 0; id < 3; id++) {
		std::string shape = "";
		fin >> shape;

		if (shape == "SMALL") {
			shape += "_";

			std::string action = "";

			for (int i = 0; i < 10; i++) {
				int numAnimation;
				fin >> action >> numAnimation;

				std::string key = shape + action;
				animations[key] = std::make_unique<AnimationManager>(sheet, 0);

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

			for (int i = 0; i < 11; i++) {
				int numAnimation;
				fin >> action >> numAnimation;

				std::string key = shape + action;
				animations[key] = std::make_unique<AnimationManager>(sheet, 0);

				for (int j = 0; j < numAnimation; j++) {
					float x, y, width, height;
					fin >> x >> y >> width >> height;
					animations[key]->addRect(Rectangle({ x, y, width, height }));
				}
			}
		}

		if (shape == "FIRE") {
			shape += "_";
			std::string action = "";

			for (int i = 0; i < 9; i++) {
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

	}
	fin.close(); 
}

void Character::powerUp(PowerUpType t){
	IShapeState *tmp = nullptr; 
	switch (t) {
	case PowerUpType::MUSHROOM:
		if (Sstate -> getShapeState() == "SMALL"){
			tmp = Sstate; 
			Sstate = new TransformedState();
			delete tmp;
		}
		break; 
	case PowerUpType::FIRE_FLOWER:
		if (Sstate -> getShapeState() == "SMALL"){
			tmp = Sstate; 
			Sstate = new TransformedState();
			delete tmp;
		}
		else{
			tmp = Sstate; 
			Sstate = new FireState();		
			delete tmp;
		}
		
		break; 
	case PowerUpType::STAR: 

		break;
	default:
		throw GameException("There is other type of power up !"); 
		break; 
	}
}

void Character::shootFireball(){
	if (IsKeyPressed(KEY_F) && Sstate->canShootFire()) {
		delete Mstate; 
		Mstate = new ShootState(); 
		
		updateShape(); 
		updateHitbox(); 

		Vector2 startPos = movement->getPosition(); 
		startPos.x += (movement->isFacingRight() ? 15 : -5); 
		startPos.y += 5;

        fireballs.emplace_back(new Fireball(startPos, movement->isFacingRight()));
		auto [w, h] = activeAnimation->getCurrentShape(); 
		fireballs.back() ->setGroundLevel(groundLevel); 
    }
}

void Character::cleanFireballs(){
    fireballs.erase(
        std::remove_if(fireballs.begin(), fireballs.end(), [](const auto &fb) { return !fb->isActive(); }),
        fireballs.end()
    );
}

void Character::adaptCollision(const Rectangle &rect){
	movement->adaptCollision(rect, Mstate); 
	updateShape(); 
	updateHitbox(); 
}

void Character::adaptChangePosition(){
	if(groundLevel - hitbox.height > hitbox.y){
		delete Mstate; 
		Mstate = new JumpState(); 
	}else{
		delete Mstate; 
		Mstate = new StandState(); 
	}
	
	updateShape(); 
	movement->setShape(activeAnimation->getCurrentShape()); 
	movement->setGroundLevel(groundLevel);
	updateHitbox(); 
}

void Character::setGroundLevel(float groundLevel_){
	this->groundLevel = groundLevel_;
	adaptChangePosition(); 
}

void Character::setPosition(const Vector2 &position){
	hitbox.x = position.x; 
	hitbox.y = position.y;

	movement->setPosition(position); 
	adaptChangePosition(); 
}

void Character::update(float deltaTime){
	if(movement == nullptr)
		throw GameException("Movement is null in Character::update"); 

	movement->update(deltaTime, Sstate, Mstate); 
	Mstate->update(deltaTime); 

	shootFireball(); 
	cleanFireballs();

	for (auto& fb : fireballs) 
		fb->update(deltaTime);

	if(activeAnimation)
		activeAnimation->update(deltaTime); 

	updateShape(); 
	updateHitbox(); 
}

void Character::render(){
	if(activeAnimation) 
		activeAnimation->render(movement->getPosition(), movement->isFacingRight() == false);
	
	for (auto& fireball : fireballs) 
		fireball->render(); 
}

Character::~Character() {
	delete Sstate; 
	delete Mstate; 
	delete movement; 

	for(auto &fireball : fireballs){
		delete fireball; 
		fireball = nullptr; 
	}

	Images::unloadAllTextures();
}

