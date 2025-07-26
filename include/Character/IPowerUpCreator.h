#include "PowerUp.h"

/// @brief  factory method design pattern

class IPowerUpCreator{
public: 
    virtual ~IPowerUpCreator(){}
    virtual PowerUp *create(const Vector2 &pos) const = 0; 
};


class MushroomCreator : public IPowerUpCreator{
public:
    PowerUp* create(const Vector2& pos) const override {
        return new MushroomPowerUp(pos);
    }
}; 

class NormalMushroomCreator : public IPowerUpCreator{
public:
    PowerUp* create(const Vector2& pos) const override {
        return new NormalMushroomPowerUp(pos);
    }
}; 


class FireFlowerCreator : public IPowerUpCreator{
public:
    PowerUp* create(const Vector2& pos) const override {
        return new FireFlowerPowerUp(pos);
    }
}; 

class StarCreator : public IPowerUpCreator{
public:
    PowerUp* create(const Vector2& pos) const override {
        return new StarPowerUp(pos);
    }
};

