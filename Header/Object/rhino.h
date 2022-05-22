#pragma once
#include "../gameconfig.h"
#include "object.h"

class rhino
{
    object *rh;
    float velocity;
    string state;
    int count;
    float currentTime;
    float time;

    void changeState();
    void revive();

public:
    rhino(float _velocity = 200, float position = screenWidth);
    void update(float delta_time);
    void render(RenderWindow *window);
};

rhino::rhino(float _velocity, float position)
{
    velocity = _velocity;
    state = "alive";
    currentTime = 0.0f;
    time = rand() % 1000 / 200;

    rh = new object(m_data->getTexture("r_run"), Vector2i(6, 1), Vector2i(position, bg_ground), Vector2i(40, 26), Vector2f(26, 19));

    count = col->addCreeper(rh->getHitBox());
}
void rhino::update(float delta_time)
{
    if (currentTime < time)
    {
        currentTime += delta_time;
        return;
    }
    rh->update(delta_time);
    if (state == "alive")
    {
        changeState();
    }
    else
    {
        velocity = 0;
        if (rh->getAnimation()->getCurrentFrame().x > 3)
            revive();
    }
    rh->moveObject(delta_time * (-velocity - bg_speed), 0);
}
void rhino::render(RenderWindow *window)
{
    rh->render(window);
}
void rhino::changeState()
{
    if (col->checkCreeper(count) && state == "alive")
    {
        state = "dead";
        col->delCreeper(count);
        rh->resetAnimation(m_data->getTexture("r_dead"), Vector2i(5, 1), Vector2f(26, 19), 0.25);
    }
}
void rhino::revive()
{
    state = "alive";
    currentTime = 0;
    time = rand() % 1000 * 1.0 / 200;
    rh->resetAnimation(m_data->getTexture("r_run"), Vector2i(6, 1), Vector2f(26, 19), 0.1);
    int position = screenWidth + rand() % 400 + 100;
    rh->moveObject(position - rh->getAnimation()->getPosition().x, 0);
    velocity = (rand() % 1000) % 2 * 150 + 150;
    col->addCreeper(count, rh->getHitBox());
}