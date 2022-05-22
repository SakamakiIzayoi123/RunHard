#pragma once
#include "../gameconfig.h"
#include "creep.h"
#include "rhino.h"
#include "bat.h"

class creeper_manager
{
    creep *cr;
    rhino *rh[3];
    bat *b[4];
    float time = 0.0f;

public:
    void init();
    void update(float delta_time);
    void render(RenderWindow *window);
};

void creeper_manager::init()
{
    cr = new creep();
    for (int i = 0; i < 3; i++)
    {
        rh[i] = new rhino((rand() % 1000) % 3 * 50 +50, rand() % 400 + screenWidth + i * 300);
    }
    for (int i = 0; i < 4; i++)
    {
        b[i] = new bat(Vector2f(screenWidth + 100 + 100 * i, bg_ground - rand() % 250 - 50), rand() % 2 * 150 + 150);
    }
}
void creeper_manager::update(float delta_time)
{
    for (int i = 0; i < 3; i++)
    {
        if (sc < i * 50)
            break;
        rh[i]->update(delta_time);
    }
    for (int i = 0; i < 4; i++)
    {
        if (sc < i * 40)
            break;
        b[i]->update(delta_time);
    }
    cr->update(delta_time);
}
void creeper_manager::render(RenderWindow *window)
{
    for (int i = 0; i < 3; i++)
    {
        rh[i]->render(window);
    }
    for (int i = 0; i < 4; i++)
    {
        b[i]->render(window);
    }
    cr->render(window);
}