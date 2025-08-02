#include "Object/PowerUp.h"
#include "Object/GameObject.h"
#include "Blocks/Coin.h"
#include "Exceptions.h"

/// @brief  factory method design pattern

class Creator {
protected:
    Texture2D &tex;
    std::vector<Rectangle> ani;
    Rectangle block;
public: 
    virtual ~Creator(){}
    Creator(Texture2D &tex, std::vector<Rectangle> &ani, const Rectangle& block) : tex(tex), ani(ani), block(block) {}
    virtual GameObject *create() const = 0; 
};

class CoinCreator : public Creator {
public:
    CoinCreator(Texture2D &tex, std::vector<Rectangle> &ani, const Rectangle& block) : Creator(tex, ani, block) {}
    GameObject *create() const override {
        if (ani.size() == 0)
            throw GameException("Lack of Object Infomation!");
        return new ContainCoin(tex, ani, block);
    }
};

class IPowerUpCreator : public Creator {
public:
    IPowerUpCreator(Texture2D &tex, std::vector<Rectangle> &ani, const Rectangle& block) : Creator(tex, ani, block) {}
};


class MushroomCreator : public IPowerUpCreator{
public:
    MushroomCreator(Texture2D &tex, std::vector<Rectangle> &ani, const Rectangle& block) : IPowerUpCreator(tex, ani, block) {}
    GameObject* create() const override {
        if (ani.size() == 0)
            throw GameException("Lack of Object Infomation!");
        return new MushroomPowerUp(tex, ani[0], block);
    }
}; 


class FireFlowerCreator : public IPowerUpCreator{
public:
    FireFlowerCreator(Texture2D &tex, std::vector<Rectangle> &ani, const Rectangle& block) : IPowerUpCreator(tex, ani, block) {}
    GameObject* create() const override {
        if (ani.size() == 0)
            throw GameException("Lack of Object Infomation!");
        return new FireFlowerPowerUp(tex, ani[0], block);
    }
}; 

class StarCreator : public IPowerUpCreator{
public:
    StarCreator(Texture2D &tex, std::vector<Rectangle> &ani, const Rectangle& block) : IPowerUpCreator(tex, ani, block) {}
    GameObject* create() const override {
        if (ani.size() == 0)
            throw GameException("Lack of Object Infomation!");
        return new StarPowerUp(tex, ani[0], block);
    }
};

