
#include "Squadron.hh"
#include <AEEngine.h>
#include <algorithm>

Squadron::Squadron()
{
    unsigned int colors[5] =
    {
        AE_COLORS_RED,
        AE_COLORS_ORANGE,
        AE_COLORS_YELLOW,
        AE_COLORS_BLUE,
        AE_COLORS_PURPLE
    };

    for (int row = 0; row < 5; row++)
    {
        for (int col = 0; col < 6; col++)
        {
            enemies.emplace_back(0.0f, 0.0f, colors[row]);
        }
    }
}

void Squadron::spawn()
{
    int index = 0;

    auto spawner = [&index](EnemyShip& enemy)
        {
            int row = index / 6;
            int col = index % 6;

            float x = -150.0f + col * 60.0f;
            float y = 200.0f - row * 45.0f;

            enemy.activate(x, y);

            index++;
        };

    std::for_each(enemies.begin(), enemies.end(), spawner);
}


void Squadron::Update()
{
    float dt = (float)AEGetFrameTime();

    float halfWidth = (float)AEGetSysWindowWidth() / 2.0f;
    float limit = halfWidth - 10.0f;

    auto it = std::find_if(enemies.begin(), enemies.end(), [this, limit](const EnemyShip& enemy)
        {
            if (!enemy.isActive())
            {
                return false;
            }

            if (direction > 0.0f)
            {
                return enemy.getX() + 17.0f >= limit;
            }

            return enemy.getX() - 17.0f <= -limit;
        }
    );

    if (it != enemies.end())
    {
        direction *= -1.0f;
    }

    std::for_each(enemies.begin(), enemies.end(), [this, dt](EnemyShip& enemy)
        {
            if (enemy.isActive())
            {
                enemy.move(speed * direction * dt, 0.0f);
                enemy.Update();
            }
        }
    );
}

std::vector<EnemyShip>& Squadron::getEnemies()
{
    return enemies;
}

void Squadron::Draw()
{
    auto drawing = [](EnemyShip& enemy)
        {
            if (enemy.isActive())
            {
                enemy.Draw();
            }
        };
    std::for_each(enemies.begin(), enemies.end(), drawing);
}

bool Squadron::allDestroyed() const
{
    auto it = std::find_if(enemies.begin(), enemies.end(),
        [](const EnemyShip& enemy)
            {
                return enemy.isActive();
            }
        );

    return it == enemies.end();
}




