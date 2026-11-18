#pragma once

#include <vector>
#include "Bullet.hh"

class BulletPool
{
private:
    std::vector<Bullet> bullets;

public:
    BulletPool(float speed, unsigned int color);

    std::vector<Bullet>& getBullets();

    void reset();

    void shoot(float x, float y);
    void Update();
    void Draw();
};
