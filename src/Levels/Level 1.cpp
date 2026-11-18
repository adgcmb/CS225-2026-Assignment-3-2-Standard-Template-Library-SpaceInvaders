#include <AEEngine.h>
#include <imgui/imgui.h>
#include <cstdlib>
#include <ctime>
#include "../CollisionEventManager.hh"
#include "../EventManager.hh"
#include "../Squadron.hh"
#include "../Player.hh"
#include "../Bullet.hh"
#include "../BulletPool.hh"
#include "Level 1.h"

int mode = 0;

static Squadron squadron;
static Player player(0.0f, -250.0f);
static BulletPool playerBullets(400.0f, AE_COLORS_WHITE);
static BulletPool enemyBullets(-250.0f, AE_COLORS_RED);
static EventManager eventManager;
static CollisionEventManager collisionManager(&squadron, &playerBullets, &enemyBullets, &player, &eventManager);

static float enemyShootTimer = 0.0f;

bool ShowFrameworkMenu();

void Level_1_Load()
{
}

void Level_1_Init()
{
    squadron.spawn();
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void Level_1_Update()
{
    // core keyboard shortcuts and GUI, do not delete this code!
    KeyboardInput();
    bool guiActive = ShowFrameworkMenu();

    squadron.Update();
    player.Update();

    if (AEInputKeyTriggered(' '))
    {
        playerBullets.shoot(player.getX(), player.getY() + 20.0f);
    }

    playerBullets.Update();
    enemyBullets.Update();

    enemyShootTimer += static_cast<float>(AEGetFrameTime());

    if (enemyShootTimer >= 1.0f)
    {
        enemyShootTimer = 0.0f;

        std::vector<EnemyShip*> activeEnemies;

        std::for_each(squadron.getEnemies().begin(), squadron.getEnemies().end(),
            [&](EnemyShip& enemy)
            {
                if (enemy.isActive())
                {
                    activeEnemies.push_back(&enemy);
                }
            }
        );

        if (!activeEnemies.empty())
        {
            int randomIndex = std::rand() % activeEnemies.size();

            EnemyShip* enemy = activeEnemies[randomIndex];

            enemyBullets.shoot(enemy->getX(), enemy->getY() - 20.0f);
        }
    }

    collisionManager.update();
    eventManager.notifyEvents();

    if (player.getLives() <= 0)
    {
        player.reset();
        playerBullets.reset();
        enemyBullets.reset();

        squadron.spawn();

        enemyShootTimer = 0.0f;

        return;
    }

    if (squadron.allDestroyed())
    {
        squadron.spawn();
    }
}

void Level_1_Render()
{
    // clear frame buffer, do not delete this code
    AEGfxSetClearColor(AEGfxColor(0, 0, 0));
    AEGfxClearBuffer();

    squadron.Draw();
    player.Draw();
    playerBullets.Draw();
    enemyBullets.Draw();
}

void Level_1_Free()
{

}

void Level_1_Unload()
{
}

void KeyboardInput()
{
    if (AEInputKeyTriggered('R'))
        AESetGameStateNext(AE_GS_RESTART);
    if (AEInputKeyTriggered('Q') && AEInputKeyPressed(AE_KEY_CTRL))
        AESetGameStateNext(AE_GS_QUIT);
}

bool ShowFrameworkMenu()
{
    bool isGuiActive = false;
    mode = 0;

    // show File options 
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Mode")) {

            if (ImGui::MenuItem("Restart", "1"))
                mode = 1;

            ImGui::EndMenu();
        }

        auto mSize = ImGui::GetWindowHeight();
        AEVec2 mouseVP = AEGetMouseData().position + AEVec2((float)AEGetSysWindowWidth() / 2.0f, (float)AEGetSysWindowHeight() / 2.0f);
        auto inMenu = mouseVP.y >= (AEGetSysWindowHeight() - mSize);
        isGuiActive = ImGui::IsAnyItemActive() || ImGui::IsAnyItemHovered() || inMenu;

        ImGui::EndMainMenuBar();
    }

    if (mode == 1) {
        AESetGameStateNext(AE_GS_RESTART);
    }

    return isGuiActive;
}

