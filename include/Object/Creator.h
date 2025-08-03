#ifndef CREATOR_H
#define CREATOR_H

#include "Object/PowerUp.h"
#include "Object/GameObject.h"
#include "Blocks/Coin.h"
#include "Exceptions.h"

/// @brief  factory method design pattern

class Creator {
public: 
    virtual ~Creator(){}
    virtual GameObject *create(const Rectangle &block) const = 0; 
};

class CoinCreator : public Creator {
public:
    GameObject *create(const Rectangle &block) const override {
        return new ContainCoin(block);
    }
};

class IPowerUpCreator : public Creator {
public: 
    virtual ~IPowerUpCreator(){}
    virtual PowerUp *create(const Rectangle &block) const = 0; 
};


class MushroomCreator : public IPowerUpCreator{
public:
    PowerUp* create(const Rectangle &block) const override {
        return new MushroomPowerUp(block);
    }
}; 

class NormalMushroomCreator : public IPowerUpCreator{
public:
    PowerUp* create(const Rectangle &block) const override {
        return new NormalMushroomPowerUp(block);
    }
}; 


class FireFlowerCreator : public IPowerUpCreator{
public:
    PowerUp* create(const Rectangle &block) const override {
        return new FireFlowerPowerUp(block);
    }
}; 

class StarCreator : public IPowerUpCreator{
public:
    PowerUp* create(const Rectangle &block) const override {
        return new StarPowerUp(block);
    }
};

#endif