
#pragma once

#include "Framework/entity.hh"
#include <AEEngine.h>

class Bullet : public Entity
{
private:
    float x;
    float y;
    float speed;
    bool active;
    unsigned int color;

public:
    Bullet(float x, float y, float speed, unsigned int color) : x(x), y(y), speed(speed), active(false), color(color) {}

    void activate(float newX, float newY);
    void deactivate();

    float getX() const { return x; }
    float getY() const { return y; }

    bool isActive() const;

    void Update() override;
    void Draw() override;
};
