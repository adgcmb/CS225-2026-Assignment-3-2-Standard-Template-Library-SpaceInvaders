
#include "BulletPool.hh"
#include <AEEngine.h>
#include <algorithm>

BulletPool::BulletPool(float speed, unsigned int color)
{
    bullets.reserve(10);

    for (int i = 0; i < 10; i++)
    {
        bullets.emplace_back(0.0f, 0.0f, speed, color);
    }
}


void BulletPool::reset()
{
    std::for_each(bullets.begin(), bullets.end(),
        [](Bullet& bullet)
        {
            bullet.deactivate();
        }
    );
}


void BulletPool::shoot(float x, float y)
{
    auto it = std::find_if(bullets.begin(), bullets.end(),
        [](const Bullet& bullet)
        {
            return !bullet.isActive();
        }
    );

    if (it != bullets.end())
    {
        it->activate(x, y);
    }
}


void BulletPool::Update()
{
    std::for_each(bullets.begin(), bullets.end(),
        [](Bullet& bullet)
        {
            if (bullet.isActive())
            {
                bullet.Update();
            }
        }
    );
}

void BulletPool::Draw()
{
    std::for_each(bullets.begin(), bullets.end(),
        [](Bullet& bullet)
        {
            if (bullet.isActive())
            {
                bullet.Draw();
            }
        }
    );
}

std::vector<Bullet>& BulletPool::getBullets()
{
    return bullets;
}
