#pragma once
#include "Enemy/Enemy.h"
#include "Enemy/Goomba.h"
#include "Enemy/Koopa.h"
#include "Enemy/Piranha.h"
#include "Enemy/ParaKoopa.h"
#include "Enemy/Blaze.h"
#include "Enemy/Bowser.h"

class EnemyFactory {
public:
    virtual std::unique_ptr<Enemy> createEnemy(Vector2 pos) = 0;
    virtual ~EnemyFactory() = default;
};

class GoombaFactory : public EnemyFactory {
private:
    bool isBrown;
public:
    GoombaFactory(bool isBrown) : isBrown(isBrown) {}

    std::unique_ptr<Enemy> createEnemy(Vector2 pos) override {
        return std::make_unique<Goomba>(pos, isBrown);
    }
};

class KoopaFactory : public EnemyFactory {
private:
    int type;
public:
    KoopaFactory(int type) : type(type) {}

    std::unique_ptr<Enemy> createEnemy(Vector2 pos) override {
        return std::make_unique<Koopa>(pos, type);
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

class BowserFactory : public EnemyFactory {
public:
    std::unique_ptr<Enemy> createEnemy(Vector2 pos) override {
        return std::make_unique<Bowser>(pos);
    }
};

class BlazeFactory : public EnemyFactory {
private:
    Vector2 target;
public:
    BlazeFactory(Vector2 targ = Vector2({0.0f, 0.0f})) : target(targ) {}

    std::unique_ptr<Enemy> createEnemy(Vector2 pos) override {
        return std::make_unique<Blaze>(pos, target);
    }
};