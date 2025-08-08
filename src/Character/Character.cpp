#include "Character/Character.h"
#include "Blocks/Coin.h"
#include "Character/Enemy.h"
#include "Resources/StateManager.h"
#include "States/GameOverMenu.h"
#include <iostream>
#include <cassert>
#include <algorithm>


void Player::setUp(){
	Sstate = new SmallState();
	Mstate = new StandState();
	activeAnimation = nullptr;
	shrinkOnHit = false; 
	showPlayer = false; 
}

Player::Player(CharacterType t, Vector2 pos):
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

Player::Player(CharacterType t,  float cordX, float groundLevel):
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

std::string Player::getShape_Action() const{
	assert(Mstate != nullptr);
	assert(Sstate != nullptr);

	return Sstate->getShapeState() + "_" + Mstate->getMoveState();
}

void Player::updateShape(){
	std::string animationKey = getShape_Action();

	if ((int)animationKey.size() >= 7 && animationKey.substr(0, 8) == "MORPHING") {
		animationKey = "SMALL_MORPHING";
		animations[animationKey]->setTimeSwitch(0.1f);
		
	}else if ((int)animationKey.size() >= 15 && animationKey.substr(0, 15) == "INVINCIBLE_FIRE"){
        animationKey.replace(0, 15, "INVINCIBLE_BIG");
	}

	if(activeAnimation != animations[animationKey].get()){
		activeAnimation = animations[animationKey].get();
	}

	if(activeAnimation == nullptr)
		throw GameException("Active animation is null in Player::updateShape " + animationKey);
}

void Player::updateHitbox(){
	if(movement == nullptr || activeAnimation == nullptr)
		throw GameException("Movement ptr activeAnimation is null in Player::updateHitbox");

	auto [w, h] = activeAnimation->getCurrentShape();

	if(Sstate->canBreakBrick() == 0) w = 12.5f;
	else w = 14.5f;

	movement->setShape(Vector2{w, h});

	Vector2 current = movement -> getPosition();
	hitbox = {current.x, current.y, w, h};
}

void Player::readRectAnimation(const std::string filename, Texture2D &sheet) {
	std::ifstream fin(filename);

	if (!fin.is_open())
		throw ResourceException("Can't load " + filename);


	for (int id = 0; id < 5; id++) {
		std::string shape = "";
		fin >> shape;

		if (shape == "SMALL") {
			shape += "_";

			std::string action = "";

			for (int i = 0; i < 10; i++) {
				int numAnimation;
				fin >> action >> numAnimation;

				std::string key = shape + action;
				animations[key] = std::make_unique<AnimationManager>(sheet, 0, 0.2f);

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
				animations[key] = std::make_unique<AnimationManager>(sheet, 0, 0.2f);

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


			for (int i = 0; i < 10; i++) {

				int numAnimation;
				fin >> action >> numAnimation;

				std::string key = shape + action;
				animations[key] = std::make_unique<AnimationManager>(sheet, 0, 0.2f);

				for (int j = 0; j < numAnimation; j++) {
					float x, y, width, height;
					fin >> x >> y >> width >> height;
					animations[key]->addRect(Rectangle({ x, y, width, height }));
				}
			}
		}

		if(shape == "INVINCIBLE_SMALL"){
			shape += "_";
			std::string action = "";

			for (int i = 0; i < 8; i++) {
				int numAnimation;
				fin >> action >> numAnimation;

				std::string key = shape + action;
				animations[key] = std::make_unique<AnimationManager>(sheet, 0, 0.2f);

				for (int j = 0; j < numAnimation; j++) {
					float x, y, width, height;
					fin >> x >> y >> width >> height;
					animations[key]->addRect(Rectangle({ x, y, width, height }));
					animations[key]->setTimeSwitch(0.1f);
				}
			}
		}

		if(shape == "INVINCIBLE_BIG"){
			shape += "_";
			std::string action = "";

			for (int i = 0; i < 8; i++) {
				int numAnimation;
				fin >> action >> numAnimation;

				std::string key = shape + action;
				animations[key] = std::make_unique<AnimationManager>(sheet, 0, 0.2f);

				for (int j = 0; j < numAnimation; j++) {
					float x, y, width, height;
					fin >> x >> y >> width >> height;
					animations[key]->addRect(Rectangle({ x, y, width, height }));
					animations[key]->setTimeSwitch(0.1f);
				}
			}
		}
	}
	fin.close();
}

void Player::powerUp(PowerUpType t){
	IShapeState *tmp = nullptr;
	switch (t) {
	case PowerUpType::MUSHROOM:
		if (Sstate -> canBreakBrick() == false){
			if(Sstate->isInvincible() == false)
			 	Sstate = new MorphDecorator(Sstate);
			else{
				delete Sstate; 
				Sstate = new InvincibleDecorator(new BigState()); 
			}
		}
		break;
	case PowerUpType::FIRE_FLOWER:
		if (Sstate -> getShapeState() == "SMALL"){
			tmp = Sstate;
			Sstate = new FireState();
			delete tmp;
		}
		else if(Sstate->canShootFire() == false){
			if(Sstate->isInvincible()){
				delete Sstate; 
				Sstate = new InvincibleDecorator(new FireState()); 
			}else{
				tmp = Sstate;
				Sstate = new FireState();
				delete tmp;
			}
		}

		break;
	case PowerUpType::STAR:
		if(Sstate->isInvincible() == false){
	    	Sstate = new InvincibleDecorator(Sstate);
		}

		break;
	case PowerUpType::NORMAL_MUSHROOM:

		break;
	default:
		throw GameException("There is other type of power up !");
		break;
	}
}


Fireball* Player::shootFireball(){
		Fireball *fireball = nullptr; 


	if (IsKeyPressed(KEY_F) && Sstate->canShootFire()) {
		delete Mstate;
		Mstate = new ShootState();

		updateShape();
		updateHitbox();

		Vector2 startPos = movement->getPosition();
		startPos.x += (movement->isFacingRight() ? 15 : -5);
		startPos.y += 5;


		fireball = new Fireball(startPos, movement->isFacingRight()); 
		fireball->setGroundLevel(2.0f * GetScreenHeight()); 
        fireballs.emplace_back(fireball);
    }

	return fireball; 

}

void Player::cleanFireballs(){
    fireballs.erase(
        std::remove_if(fireballs.begin(), fireballs.end(), [](const auto &fb) { return !fb->isActive(); }),
        fireballs.end()
    );
}

void Player::triggerDeath(){
	if(Mstate->isDead()){
		return; 
	}

	if (!SoundManager::getInstance().death_played)
	{
		SoundManager::getInstance().stopPlayMusic();
		SoundManager::getInstance().playDeathSound();
		SoundManager::getInstance().death_played = true;
	}

	IMoveState *tmp = Mstate;
	Mstate = new DeadState();
	delete tmp;
	tmp = nullptr;

	movement->setDisableUpdate(); 
	movement->setVelocityX(0.0f); 
	movement->setVelocityY(-200.0f); 
	movement->setGroundLevel(1000.0f); 

}


void Player::adapt_collision_with_enimies(ICollidable* other){
	if(isInvincible() || blink.isActive()) return; 

	if(movement->adapt_collision_with_enimies(other, this)) return;


	if(isBig() == false){
		triggerDeath(); 
		return; 
	}

	if(shrinkOnHit) return; 

	shrinkOnHit = true; 
	blink.reset(); 

	IMoveState *tmp = Mstate; 
	Mstate = new HitState(); 
	delete tmp; 
	tmp = nullptr; 
	showPlayer = false; 
}

void Player::adaptCollision(ICollidable* other){
	if(Mstate->isDead()){
		return; 
	}

	if (dynamic_cast<Coin*>(other))
		return;
	if (dynamic_cast<MushroomPowerUp*>(other))

	if (!isBig() && dynamic_cast<MushroomPowerUp*>(other))
		return;
	if (dynamic_cast<FireFlowerPowerUp*>(other))

	if (!canShootFire() && dynamic_cast<FireFlowerPowerUp*>(other))
		return;
	if (dynamic_cast<StarPowerUp*>(other))

	if (!isInvincible() && dynamic_cast<StarPowerUp*>(other))
		return;

	if (dynamic_cast<Fireball*>(other))
		return;

	if(dynamic_cast<Enemy*>(other)){
		adapt_collision_with_enimies(other); 
		return; 
	}


	movement->adaptCollision(other, Mstate, this); 
	updateShape(); 
	updateHitbox(); 
}

void Player::setOnGround(){
	if(Mstate-> isJumping()){
		delete Mstate;
		Mstate = new StandState();
	}

	updateShape();
	movement->setShape(activeAnimation->getCurrentShape());
	movement->setGroundLevel(groundLevel);
	movement->setOnGround();
	updateHitbox();
}

void Player::adaptChangePosition(){
	if(groundLevel - hitbox.height > hitbox.y){
		if(!Mstate->isDead()){
			delete Mstate;
			Mstate = new JumpState();
		}
	}else{
		delete Mstate;
		Mstate = new StandState();
		hitbox.y = groundLevel - hitbox.height;

	}

	updateShape();
	movement->setShape(activeAnimation->getCurrentShape());
	movement->setGroundLevel(groundLevel);
	updateHitbox();
}

void Player::setGroundLevel(float groundLevel_){
	this->groundLevel = groundLevel_;
	adaptChangePosition();
}

void Player::setPosition(const Vector2 &position){
	hitbox.x = position.x;
	hitbox.y = position.y;

	movement->setPosition(position);
	adaptChangePosition();
}


void Player::animationTransform(){

}

void Player::update(float deltaTime){
	if(movement == nullptr)
		throw GameException("Movement is null in Player::update");


	if(IsKeyPressed(KEY_Q)){
		if (Sstate -> getShapeState() == "SMALL"){
			Sstate = new MorphDecorator(Sstate);
		}
	}

	if(IsKeyPressed(KEY_W)){
		if (Sstate -> getShapeState() == "SMALL"){
			IShapeState *tmp = Sstate;
			Sstate = new FireState();
			delete tmp;
		}
		else if(Sstate->canShootFire() == false){
			IShapeState *tmp = Sstate;
			Sstate = new FireState();
			delete tmp;
		}
	}

	if(IsKeyPressed(KEY_E)){
		if(Sstate->isInvincible() == false){
	    	Sstate = new InvincibleDecorator(Sstate);
		}	
	}


	if (auto morph = dynamic_cast<MorphDecorator*>(Sstate)) {
		IShapeState* next = morph->update(deltaTime);

		if (next) {
			delete Sstate;
			Sstate = next;
		}else{
			if(activeAnimation)
				activeAnimation->update(deltaTime);

			adaptChangePosition();
			return;
		}
	}
	else if (auto inv = dynamic_cast<InvincibleDecorator*>(Sstate)) {
		IShapeState* next = inv->update(deltaTime);
		if (next) {
			delete Sstate;
			Sstate = next;
		}
	}

	cleanFireballs();

	for (auto& fb : fireballs)
		fb->update(deltaTime);
	
	showPlayer = blink.update(deltaTime); 
	Mstate->update(deltaTime);

	if(shrinkOnHit){
		if(activeAnimation)
			activeAnimation->update(deltaTime);
		
		updateShape();
		movement->setShape(activeAnimation->getCurrentShape());
		movement->setGroundLevel(groundLevel);
		updateHitbox();		

		if(activeAnimation->isOnePeriodPassed()){
			delete Sstate;
			delete Mstate;  
			Sstate = new SmallState(); 
			Mstate = new StandState(); 
			
			updateShape();
			movement->setShape(activeAnimation->getCurrentShape());
			movement->setGroundLevel(groundLevel);
			updateHitbox();		
			shrinkOnHit = false; 
		}
		return; 
	}

	movement->update(deltaTime, Sstate, Mstate);
 

	if(activeAnimation)
		activeAnimation->update(deltaTime);

	// if(Mstate->isJumping()){
	// 	movement->setFootHeightFactor(0.2f);
	// }else movement->setFootHeightFactor(0.1f);
	// std::cout << "GroundLevel: " << groundLevel << ' ' << Mstate->getMoveState() << ' ' << movement->getPosition().x << ' ' << movement->getPosition().y << '\n';

	updateShape();
	updateHitbox();
}

void Player::render(){

	if(activeAnimation){
		if(showPlayer){
			activeAnimation->render(movement->getPosition(), movement->isFacingRight() == false);
		}
	}

	for (auto& fireball : fireballs)
		fireball->render();
}

Player::~Player() {
	delete Sstate;
	delete Mstate;
	delete movement;

	for(auto &fireball : fireballs){
		delete fireball;
		fireball = nullptr;
	}

	Images::unloadAllTextures();
}



void Player::run_from_a_to_b(float startX, float endX){
	if(movement->isDoneLerpMoving() == false){
		return;
	}

	if(startX > endX){
		std::cout << "Can't go from " << startX << " to " << endX << '\n';
		return; 
	}

	if(dynamic_cast<RunState*>(Mstate) == nullptr){
		delete Mstate; 
		Mstate = new RunState(); 
		updateShape();
		updateHitbox();
	}

	movement->run_from_a_to_b(startX, endX);
}