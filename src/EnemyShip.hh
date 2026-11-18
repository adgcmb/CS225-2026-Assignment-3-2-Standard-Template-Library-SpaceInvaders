
#pragma once

#include "Framework/entity.hh"

class EnemyShip : public Entity
{
    private:
        float x;
        float y;
        bool active;
        unsigned int color;
    
    public:
        EnemyShip(float x, float y, unsigned int color) : x(x), y(y), active(false), color(color) {}
    
        void activate(float newX, float newY);
        void deactivate();

        float getX() const { return x; }
        float getY() const { return y; }
    
        bool isActive() const;
    
        void move(float dx, float dy);
    
        void Update() override;
        void Draw() override;
};