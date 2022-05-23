#pragma once
#include "../gameconfig.h"
#include "object.h"

using namespace sf;

class bat
{
    object *b;
    float velocity;
    float angle;
    string state;
    int count;
    float time;
    float currentTime;

    void changeState();
    void revive();

public:
    bat(Vector2f position, float _velocity = 100, float _angle = 0);
    void update(float delta_time);
    void render(RenderWindow *window);
};

bat::bat(Vector2f position, float _velocity, float _angle)
{
    velocity = _velocity;
    angle = _angle;
    state = "alive";
    currentTime = 0;
    time = rand() % 1000 / 200;

    b = new object(m_data->getTexture("b1_flying"), Vector2i(7, 1), Vector2i(position), Vector2i(20, 20), Vector2f(23, 15));

    count = col->addCreeper(b->getHitBox());
}
void bat::update(float delta_time)
{
    b->update(delta_time);
    if (state == "alive")
    {
        changeState();
    }
    else
    {
        velocity = 0;
        if (b->getAnimation()->getCurrentFrame().x > 3)
            revive();
    }
    b->moveObject(delta_time * (-velocity - bg_speed), 0);
    if (b->getAnimation()->getPosition().x < 0)
        revive();
}
void bat::render(RenderWindow *window)
{
    b->render(window);
}
void bat::changeState()
{
    if (col->checkCreeper(count) && state == "alive")
    {
        state = "dead";
        m_data->getSound("mixkit-creature-cry-of-hurt-2208")->setVolume(playMusic ? 30 : 0);
        m_data->getSound("mixkit-creature-cry-of-hurt-2208")->play();
        col->delCreeper(count);
        b->resetAnimation(m_data->getTexture("b1_dead"), Vector2i(5, 1), Vector2f(23, 15), 0.25);
    }
}
void bat::revive()
{
    state = "alive";
    b->resetAnimation(m_data->getTexture("b1_flying"), Vector2i(7, 1), Vector2f(23, 19), 0.1);
    int positionX = screenWidth + rand() % 1000 + 100;
    int positionY = bg_ground - 50 - rand() % 250;
    b->moveObject(positionX - b->getAnimation()->getPosition().x, positionY - b->getAnimation()->getPosition().y);
    velocity = (rand() % 100) % 4 * 50 + 150;
    col->addCreeper(count, b->getHitBox());
}