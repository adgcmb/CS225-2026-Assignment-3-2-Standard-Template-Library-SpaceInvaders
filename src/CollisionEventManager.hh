#pragma once

#include "EventManager.hh"

class Squadron;
class BulletPool;
class Player;

class CollisionEventManager
{
private:
    Squadron* ships;
    BulletPool* bullets;
    EventManager* eventManager;
    Player* player;
    BulletPool* enemyBullets;

public:
    CollisionEventManager(Squadron* ships, BulletPool* bullets, BulletPool* enemyBullets, Player* player, EventManager* eventManager) : ships(ships), bullets(bullets), enemyBullets(enemyBullets), player(player), eventManager(eventManager) {}

    void update();
};