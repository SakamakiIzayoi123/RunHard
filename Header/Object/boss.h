#pragma once
#include "object.h"
#include "../gameconfig.h"

using namespace sf;

class boss
{
public:
    boss();
    void update(float deltaTime, Vector2f position);
    void render(RenderWindow *window);
    hitBox *getHitBox() { return monster->getHitBox(); }
    hitBox *getHitBoxPoison() { return arrow->getHitBox(); }
    void setState(string state) { this->state = state; }
    void move(float x, float y) { monster->moveObject(x, y); }

private:
    object *monster;
    string state;
    Vector2f velocity;
    float time = 0.0f;
    float time_attack = 0.0f;
    bool delArrow = false;

    object *arrow;
    string arrow_state;

    string changeState(Vector2f position);
    void jump(float deltaTime);
    void attack(float deltaTime);
    void hurt(float deltaTime);
    void updateArrow(float deltaTime);
};

boss::boss()
{
    monster = new object(m_data->getTexture("b_Jump"), Vector2i(6, 3), Vector2i(100, bg_ground - 30), Vector2i(150, 90), Vector2f(115, 165), false);
    monster->getAnimation()->setScale(-1, 1);
    arrow = nullptr;
    state = "b_Jump";

    col->setBoss(monster->getHitBox());
}
void boss::render(RenderWindow *window)
{
    monster->render(window);
    if (arrow != nullptr)
        arrow->render(window);
}
void boss::update(float deltaTime, Vector2f position)
{
    time_attack += deltaTime;
    updateArrow(deltaTime);
    if (monster->getAnimation()->getCurrentFrame().x == monster->getAnimation()->getFrameNum().x - 2 &&
        monster->getAnimation()->getCurrentFrame().y == monster->getAnimation()->getFrameNum().y - 1)
    {
        state = changeState(position);
    }
    if (col->checkBoss())
    {
        hurt(deltaTime);
    }
    else if (state == "b_Attack")
    {
        attack(deltaTime);
    }
    if (state == "b_Hurt")
    {
        hurt(deltaTime);
    }
    else if (state == "b_Jump")
        jump(deltaTime);
    if (monster->getAnimation()->getPosition().x < -87)
    {
        monster->moveObject(-87 - monster->getAnimation()->getPosition().x, 0);
    }
}
string boss::changeState(Vector2f position)
{
    if (position.x - monster->getAnimation()->getPosition().x > 100 && time_attack > monster_time_attack)
    {
        monster->resetAnimation(m_data->getTexture("b_Attack"), Vector2i(6, 3), Vector2f(94.5, 79.5), 0.1, false);
        monster->getAnimation()->setScale(-1, 1);
        time_attack = 0;
        return "b_Attack";
    }
    else
    {
        monster->resetAnimation(m_data->getTexture("b_Jump"), Vector2i(6, 3), Vector2f(115, 165), 0.15, false);
        monster->getAnimation()->setScale(-1, 1);
        return "b_Jump";
    }
}
void boss::jump(float deltaTime)
{
    if (state != "b_Jump")
    {
        monster->resetAnimation(m_data->getTexture("b_Jump"), Vector2i(6, 3), Vector2f(115, 165), 0.15, false);
        state = "b_Jump";
        monster->getAnimation()->setScale(-1, 1);
    }
    Vector2i position = monster->getAnimation()->getCurrentFrame();
    int i = position.x + 6 * position.y + 1;
    if (i < 5 || i > 12)
    {
        velocity.x = 0;
    }
    else
    {
        velocity.x = monster_speed;
    }
    monster->moveObject(velocity.x * deltaTime - bg_speed * deltaTime, 0);
    if (i != 1 || time > 0.1)
    {
        monster->update(deltaTime);
        time = 0;
    }
    else
    {
        time += deltaTime;
    }
}
void boss::attack(float deltaTime)
{
    time += deltaTime;
    if (state != "b_Attack")
    {
        monster->resetAnimation(m_data->getTexture("b_Attack"), Vector2i(6, 3), Vector2f(94.5, 79.5), 0.1, false);
        state = "b_Attack";
        monster->getAnimation()->setScale(-1, 1);
    }
    m_data->getSound("impactsplat03")->setVolume(playMusic ? 100 : 0);
    m_data->getSound("impactsplat03")->play();
    velocity = Vector2f(0, 0);
    Vector2i pos = monster->getAnimation()->getCurrentFrame();
    monster->moveObject(-bg_speed * deltaTime, 0);
    monster->update(deltaTime);
    if (pos.x + 1 + pos.y * 6 == 14 && arrow == nullptr)
    {
        pos = (Vector2i)(monster->getAnimation()->getPosition());
        arrow = new object(m_data->getTexture("p_PoisonSpit"), Vector2i(4, 3), Vector2i(pos.x + 90, pos.y + 20), Vector2i(50, 18), Vector2f(30.5, 10));
        arrow_state = "p_PoisonSpit";
        arrow->getAnimation()->setScale(-1, 1);
        col->setPoison(arrow->getHitBox());
    }
}
void boss::hurt(float deltaTime)
{
    if (state != "b_Hurt")
    {
        if (m_data->getSound("monster-hurt")->getStatus() != SoundSource::Playing)
        {
            m_data->getSound("monster-hurt")->setVolume(playMusic ? 100 : 0);
            m_data->getSound("monster-hurt")->play();
        }
        monster->resetAnimation(m_data->getTexture("b_Hurt"), Vector2i(2, 2), Vector2f(93, 88), 0.2);
        state = "b_Hurt";
        monster->getAnimation()->setScale(-1, 1);
    }
    velocity = Vector2f(0, 0);
    monster->moveObject(-bg_speed * deltaTime, 0);
    monster->update(deltaTime);
    Vector2i temp = monster->getAnimation()->getCurrentFrame();
}
void boss::updateArrow(float deltaTime)
{
    if (arrow == nullptr)
        return;
    if (delArrow)
    {
        col->delPoison();
        delArrow = false;
    }
    arrow->update(deltaTime);
    if (col->checkPoison() && arrow_state == "p_PoisonSpit")
    {
        delArrow = true;
        arrow_state = "p_PoisonImpact";
        arrow->resetAnimation(m_data->getTexture("p_PoisonImpact"), Vector2i(4, 3), Vector2f(23.5, 37.5), 0.05);
        arrow->getAnimation()->setScale(-1, 1);
    }
    if (arrow_state == "p_PoisonSpit")
    {
        arrow->moveObject(monster_speed_poison * deltaTime, 0);
        if (arrow->getAnimation()->getPosition().x > screenWidth + 50)
        {
            arrow = nullptr;
            col->delPoison();
        }
    }
    else
    {
        arrow->moveObject(-bg_speed * deltaTime, 0);
        Vector2i temp = arrow->getAnimation()->getCurrentFrame();
        if (temp.x + temp.y * 4 == 10)
            arrow = nullptr;
    }
}