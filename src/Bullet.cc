
#include "Bullet.hh"

void Bullet::activate(float newX, float newY)
{
    x = newX;
    y = newY;
    active = true;
}

void Bullet::deactivate()
{
    active = false;
}

bool Bullet::isActive() const
{
    return active;
}

void Bullet::Update()
{
    if (!active)
    {
        return;
    }


    float dt = (float)AEGetFrameTime();

    y += speed * dt;

    float limit = (float)AEGetSysWindowHeight() / 2.0f;

    if (y > limit || y < -limit)
    {
        deactivate();
    }
}

void Bullet::Draw()
{
    if (!active)
    {
        return;
    }

    AEGfxRect(x, y, 0.0f, 5.0f, 12.0f, color);
}
