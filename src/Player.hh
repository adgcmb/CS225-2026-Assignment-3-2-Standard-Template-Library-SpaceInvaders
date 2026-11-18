
#pragma once

#include "Framework/entity.hh"
#include <AEEngine.h>

class Player : public Entity
{
private:
    float x;
    float y;
    float speed;
    unsigned int color;
    int lives;

public:
    Player(float x, float y) : x(x), y(y), speed(0.1f), color(AE_COLORS_GREEN), lives(3) {}

    float getX() const {return x;}
    float getY() const {return y;}

    int getLives() const { return lives; }
    void loseLife();

    void reset();

    void Update() override;
    void Draw() override;
};
