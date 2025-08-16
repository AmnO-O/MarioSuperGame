#pragma once
#include "Character/Enemy.h"
#include "Character/Goomba.h"
#include "Character/Koopa.h"
#include "Character/Piranha.h"
#include "Character/ParaKoopa.h"
#include "Character/Bowser.h"

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
public:
    std::unique_ptr<Enemy> createEnemy(Vector2 pos) override {
        return std::make_unique<Blaze>(pos);
    }
};