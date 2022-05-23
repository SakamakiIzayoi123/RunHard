#pragma once
#include "object.h"
#include "../gameconfig.h"

using namespace sf;

class creep
{
    object *cr;
    int move_creep;
    float velocity;
    string state;
    string temp_state;
    bool right_direction;
    bool end = false;
    int count;

    hitBox *attackBox;

    Vector2i frame_number;
    float frame_time;

    void changeState(Vector2f pos);
    void setState(string _state);
    void revive(int left, int right);

public:
    creep();
    void update(float delta_time);
    void render(RenderWindow *window);
};

creep::creep()
{
    move_creep = 0;
    velocity = creeper_speed;
    state = "c_Idle";
    temp_state = "c_Idle";
    right_direction = true;

    frame_number = Vector2i(4, 1);
    frame_time = 0.1;

    cr = new object(m_data->getTexture(state), frame_number, Vector2i(screenWidth + 300, bg_ground), Vector2i(26, 32), Vector2f(32, 48));

    count = col->addCreeper(cr->getHitBox());
}
void creep::changeState(Vector2f _pos)
{
    Vector2f pos = cr->getAnimation()->getPosition();
    temp_state = "c_Idle";
    if (pos.x > _pos.x)
        right_direction = false;
    else
        right_direction = true;
    if (abs(_pos.x - pos.x) < 200)
    {
        move_creep = right_direction ? 1 : -1;
        temp_state = "c_Run";
    }
    else
        move_creep = 0;
    if (abs(pos.x - _pos.x) < 45)
    {
        move_creep = 0;
        temp_state = "c_Attack";
    }
    if (col->getArrow() != nullptr)
    {
        Vector2f m_pos = col->getArrow()->getPosition();
        if (abs(pos.x - m_pos.x) < 125)
        {
            move_creep = 0;
            temp_state = "c_Attack";
        }
    }

    if (temp_state != state || cr->getAnimation()->getCurrentFrame().x == frame_number.x - 1)
        setState(temp_state);
}
void creep::update(float delta_time)
{
    if (col->checkCreeper(count) && state != "c_Death")
    {
        state = "c_Death";
        setState(state);
        col->delCreeper(count);
    }
    if (cr->getAnimation()->getCurrentFrame().x == frame_number.x - 1 || state == "c_Idle" || state == "c_Run")
    {
        if (state != "c_Death")
        {
            changeState(col->getCharacter()->getPosition());
        }
        else
            revive(screenWidth, screenWidth + 300);
    }
    cr->update(delta_time);
    if (state == "c_Attack" && cr->getAnimation()->getCurrentFrame().x >= 1)
    {
        Vector2f pos = cr->getAnimation()->getPosition();
        int i = right_direction ? -1 : 1;
        attackBox = new hitBox(Vector2i(17, 40), Vector2i(pos.x - 24 * i, pos.y - 3));
        col->setTemp(attackBox);
    }
    else
    {
        col->delTemp();
        attackBox = nullptr;
    }
    cr->moveObject(delta_time * (velocity * move_creep - bg_speed), 0);
}
void creep::render(RenderWindow *window)
{
    if (!right_direction)
        cr->getAnimation()->setScale(-1, 1);
    else
        cr->getAnimation()->setScale(1, 1);
    cr->render(window);
}
void creep::setState(string _state)
{
    state = _state;
    if (_state == "c_Idle")
    {
        frame_number = Vector2i(4, 1);
        frame_time = 0.25;
    }
    else if (_state == "c_Run")
    {
        frame_number = Vector2i(8, 1);
        frame_time = 0.1;
    }
    else if (_state == "c_Death")
    {
        frame_number = Vector2i(6, 1);
        frame_time = 0.15;
        move_creep = 0;
    }
    else if (_state == "c_Attack")
    {
        frame_number = Vector2i(5, 1);
        frame_time = 0.1;
    }
    cr->resetAnimation(m_data->getTexture(state), frame_number, Vector2f(32, 48), frame_time);
}
void creep::revive(int left = screenWidth, int right = (screenWidth + 300))
{
    move_creep = 0;
    temp_state = "c_Idle";
    setState(temp_state);
    int temp = 200 + left;
    cr->moveObject(temp - cr->getAnimation()->getPosition().x, 0);
    col->addCreeper(count, cr->getHitBox());
}