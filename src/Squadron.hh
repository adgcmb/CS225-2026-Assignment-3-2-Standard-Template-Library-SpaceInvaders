#pragma once

#include <vector>
#include "EnemyShip.hh"

class Squadron
{
    private:
        std::vector<EnemyShip> enemies;
        float speed = 50.0f;
        float direction = 1.0f;
    
    public:
        Squadron();

        std::vector<EnemyShip>& getEnemies();
    
        void spawn();
        void Update();
        void Draw();
    
        bool allDestroyed() const;
};