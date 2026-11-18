
#include "Player.hh"

void Player::loseLife()
{
    if (lives > 0)
    {
        lives--;
    }
}

void Player::reset()
{
    x = 0.0f;
    y = -250.0f;
    lives = 3;
}

void Player::Update()
{
    float dt = (float)AEGetFrameRate();

    if (AEInputKeyPressed('A'))
    {
        x -= speed * dt;
    }

    if (AEInputKeyPressed('D'))
    {
        x += speed * dt;
    }

    float limit = (float)AEGetSysWindowWidth() / 2.0f - 28.0f;

    if (x > limit)
    {
        x = limit;
    }

    if (x < -limit)
    {
        x = -limit;
    }

}

void Player::Draw()
{
    AEGfxRect(x, y, 0.0f, 34.0f, 18.0f, color);
}
