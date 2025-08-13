#ifndef CREATOR_H
#define CREATOR_H

#include "Object/PowerUp.h"
#include "Object/GameObject.h"
#include "Blocks/Coin.h"
#include "Exceptions.h"
#include <unordered_map>
#include <string> 
#include <iostream>
#include <functional>
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
    using CreatorFunc = std::function<PowerUp*(std::istream&)>;
    std::unordered_map<std::string, CreatorFunc> registry;
public:
    IPowerUpCreator() {
        // Đăng ký từng loại
        registry["MUSHROOM"] = [](std::istream &fin) {
            Rectangle rect;
            fin >> rect.x >> rect.y >> rect.width >> rect.height;
            return new MushroomPowerUp(rect);
        };
        registry["NORMAL_MUSHROOM"] = [](std::istream &fin) {
            Rectangle rect;
            fin >> rect.x >> rect.y >> rect.width >> rect.height;
            return new NormalMushroomPowerUp(rect);
        };
        registry["FIRE_FLOWER"] = [](std::istream &fin) {
            Rectangle rect;
            fin >> rect.x >> rect.y >> rect.width >> rect.height;
            return new FireFlowerPowerUp(rect);
        };
        registry["STAR"] = [](std::istream &fin) {
            Rectangle rect;
            fin >> rect.x >> rect.y >> rect.width >> rect.height;
            return new StarPowerUp(rect);
        };
    }

    PowerUp* createFromStream(const std::string &type, std::istream &fin) const {
        auto it = registry.find(type);
        return (it != registry.end()) ? it->second(fin) : nullptr;
    }

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