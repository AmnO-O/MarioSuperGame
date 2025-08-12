#pragma once
#include "Character/Enemy.h"
#include "Character/Goomba.h"
#include "Character/Koopa.h"
#include "Character/Piranha.h"
#include "Character/ParaKoopa.h"

class EnemyFactory {
public:
    virtual std::unique_ptr<Enemy> createEnemy(Vector2 pos) = 0;
    virtual ~EnemyFactory() = default;
};

class GoombaFactory : public EnemyFactory {
public:
    std::unique_ptr<Enemy> createEnemy(Vector2 pos) override {
        return std::make_unique<Goomba>(pos);
    }
};

class KoopaFactory : public EnemyFactory {
public:
    std::unique_ptr<Enemy> createEnemy(Vector2 pos) override {
        return std::make_unique<Koopa>(pos);
    }
};

class PiranhaFactory : public EnemyFactory {
private:
    bool isGoing;
public:
    PiranhaFactory(bool ig) : isGoing(ig) {}

    std::unique_ptr<Enemy> createEnemy(Vector2 pos) override {
        return std::make_unique<Piranha>(pos, isGoing);
    }
};

class ParaKoopaFactory : public EnemyFactory {
public:
    std::unique_ptr<Enemy> createEnemy(Vector2 pos) override {
        return std::make_unique<ParaKoopa>(pos);
    }
};
