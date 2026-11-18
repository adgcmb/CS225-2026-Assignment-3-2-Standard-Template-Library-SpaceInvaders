
#include "EnemyShip.hh"
#include <AEEngine.h>

void EnemyShip::activate(float newX, float newY)
{
    x = newX;
    y = newY;
    active = true;
}

void EnemyShip::deactivate()
{
    active = false;
}

bool EnemyShip::isActive() const
{
    return active;
}

void EnemyShip::Update()
{
    if (!active)
        return;
}

void EnemyShip::Draw()
{
    if (!active)
    {
        return;
    }

    AEGfxRect(x, y, 0.0f, 34.0f, 18.0f, color);
}

void EnemyShip::move(float dx, float dy)
{
    x += dx;
    y += dy;
}
