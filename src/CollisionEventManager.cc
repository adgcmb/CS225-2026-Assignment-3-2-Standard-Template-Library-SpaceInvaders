#include "CollisionEventManager.hh"
#include "Squadron.hh"
#include "BulletPool.hh"
#include "Player.hh"
#include <AEEngine.h>
#include <algorithm>


void CollisionEventManager::update()
{
    std::for_each(bullets->getBullets().begin(), bullets->getBullets().end(),
        [&](Bullet& bullet)
        {
            if (!bullet.isActive())
            {
                return;
            }

            auto it = std::find_if(ships->getEnemies().begin(), ships->getEnemies().end(),
                [&](EnemyShip& enemy)
                {
                    if (!enemy.isActive())
                    {
                        return false;
                    }

                    AEVec2 bulletPosition = {bullet.getX(), bullet.getY()};

                    AEVec2 enemyPosition = {enemy.getX(), enemy.getY()};

                    return AEStaticRectToStaticRect(&bulletPosition, 5.0f, 12.0f, &enemyPosition, 34.0f, 18.0f);
                }
            );

            if (it != ships->getEnemies().end())
            {
                EnemyShip& enemy = *it;

                eventManager->addEvent(
                    [&bullet, &enemy]()
                    {
                        bullet.deactivate();
                        enemy.deactivate();
                    });
            }
        }
    );

    std::for_each(enemyBullets->getBullets().begin(), enemyBullets->getBullets().end(),
        [&](Bullet& bullet)
        {
            if (!bullet.isActive())
            {
                return;
            }

            AEVec2 bulletPosition = {bullet.getX(), bullet.getY()};

            AEVec2 playerPosition = {player->getX(), player->getY()};

            if (AEStaticRectToStaticRect(&bulletPosition, 5.0f, 12.0f, &playerPosition, 34.0f, 18.0f))
            {
                eventManager->addEvent(
                    [this, &bullet]()
                    {
                        bullet.deactivate();
                        player->loseLife();
                    });
            }
        }
    );

}
