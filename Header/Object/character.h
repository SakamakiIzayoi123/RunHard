#pragma once
#include "object.h"
#include "../gameconfig.h"

using namespace sf;

class character
{
    object *player;
    Vector2i move_character;
    Vector2f velocity;
    string state;
    string temp_state;
    bool right_direction;
    bool end = false;

    bool double_jump = true;
    float time_jump = 0;

    object *arrow;
    int arrow_direction;
    string arrow_state;
    float time_attack = 0;

    Vector2i frame_number;
    float frame_time;

    void move(float delta_time);
    void attack(float delta_time);
    void death(float delta_time);
    void updateArrow(float delta_time);
    void changeState(string _state);

public:
    character();
    //~character();
    void update(float delta_time);

    void render(RenderWindow *window);
    bool isDead() { return end; }
    hitBox *getHitBox() { return player->getHitBox(); }
    Vector2f getPosition() { return player->getAnimation()->getPosition(); }
};
character::character()
{
    move_character = Vector2i(0, 0);
    velocity = Vector2f(character_speed, 0);
    state = "ch_Idle";
    temp_state = "ch_Idle";
    frame_number = Vector2i(8, 1);
    right_direction = true;

    arrow = nullptr;
    player = new object(m_data->getTexture("ch_Idle"), Vector2i(8, 1), Vector2i(screenWidth / 2, bg_ground), Vector2i(24, 32), Vector2f(63, 60));

    col->setCharacter(player->getHitBox());
}
void character::changeState(string _state)
{
    if (state == _state)
        return;
    if (_state == "ch_Idle")
    {
        state = "ch_Idle";
        frame_number = Vector2i(8, 1);
        frame_time = 0.1;
    }
    if (_state == "ch_Run")
    {
        state = "ch_Run";
        frame_number = Vector2i(8, 1);
        frame_time = 0.05;
    }
    if (_state == "ch_Jump")
    {
        state = "ch_Jump";
        frame_number = Vector2i(4, 1);
        frame_time = 0.125;
        m_data->getSound("jumpland")->setVolume(playMusic ? 100 : 0);
        m_data->getSound("jumpland")->play();
    }
    if (_state == "ch_Fall")
    {
        state = "ch_Fall";
        frame_number = Vector2i(2, 1);
        frame_time = 0.25;
    }
    if (_state == "ch_Attack")
    {
        state = "ch_Attack";
        frame_number = Vector2i(14, 1);
        frame_time = 0.075;
    }
    if (_state == "ch_Death")
    {
        state = "ch_Death";
        frame_number = Vector2i(24, 1);
        frame_time = 0.1;
        m_data->getSound("202037__thestigmata__man-die")->setVolume(playMusic ? 50 : 0);
        m_data->getSound("202037__thestigmata__man-die")->play();
    }
    player->resetAnimation(m_data->getTexture(state), frame_number, Vector2f(63, 60), frame_time);
}
void character::move(float delta_time)
{
    if (player->getAnimation()->getPosition().y == bg_ground)
    {
        move_character = Vector2i(0, 0);
        temp_state = "ch_Idle";
        double_jump = true;
        if (Keyboard::isKeyPressed(Keyboard::Numpad3) || Keyboard::isKeyPressed(Keyboard::D))
        {
            move_character.x = 1;
            right_direction = true;
            temp_state = "ch_Run";
        }
        else if (Keyboard::isKeyPressed(Keyboard::Numpad1) || Keyboard::isKeyPressed(Keyboard::A))
        {
            move_character.x = -1;
            right_direction = false;
            temp_state = "ch_Run";
        }
        if (Keyboard::isKeyPressed(Keyboard::Z) || Keyboard::isKeyPressed(Keyboard::W))
        {
            move_character.y = 1;
            velocity.y = character_jump_speed;
            temp_state = "ch_Jump";
            time_jump = 0;
        }
    }
    else
    {
        if (double_jump && time_jump > 0.45 && (Keyboard::isKeyPressed(Keyboard::Z) || Keyboard::isKeyPressed(Keyboard::W)))
        {
            temp_state = "ch_Jump";
            // time_jump = 1000;
            move_character.y = 1;
            velocity.y = character_jump_speed;
            double_jump = false;
            if (Keyboard::isKeyPressed(Keyboard::Numpad3) || Keyboard::isKeyPressed(Keyboard::D))
            {
                move_character.x = 1;
                right_direction = true;
            }
            else if (Keyboard::isKeyPressed(Keyboard::Numpad1) || Keyboard::isKeyPressed(Keyboard::A))
            {
                move_character.x = -1;
                right_direction = false;
            }
        }
        time_jump += delta_time;
        velocity.y -= 1000 * delta_time;
        if (velocity.y < 0)
        {
            temp_state = "ch_Fall";
        }
    }

    if (getPosition().x > screenWidth || getPosition().x < 20)
        velocity.x = 0;
    else
        velocity.x = character_speed;
    player->moveObject(velocity.x * move_character.x * delta_time, -velocity.y * delta_time * move_character.y);
    changeState(temp_state);
    if (player->getAnimation()->getPosition().y > bg_ground)
        player->moveObject(0, bg_ground - player->getAnimation()->getPosition().y);
    player->update(delta_time);
}
void character::attack(float delta_time)
{
    temp_state = "ch_Attack";
    time_attack = 0;
    changeState(temp_state);
    if (player->getAnimation()->getCurrentFrame().x == 9 && arrow == nullptr)
    {
        m_data->getSound("Tieng-ban-cung-ten-www_tiengdong_com")->setVolume(playMusic ? 100 : 0);
        m_data->getSound("Tieng-ban-cung-ten-www_tiengdong_com")->play();
        arrow_state = "ar_ArrowSpit";
        arrow = new object(m_data->getTexture("ar_ArrowSpit"), Vector2i(1, 1), Vector2i(player->getAnimation()->getPosition().x, player->getAnimation()->getPosition().y - 8), Vector2i(21, 3), Vector2f(12, 6));
        if (right_direction)
            arrow_direction = 1;
        else
            arrow_direction = -1;
        col->setArrow(arrow->getHitBox());
    }
    player->update(delta_time);
}
void character::death(float delta_time)
{
    temp_state = "ch_Death";

    if (player->getAnimation()->getPosition().y == bg_ground)
    {
        changeState(temp_state);
        if (player->getAnimation()->getCurrentFrame().x < 23)
            player->update(delta_time);
        else
            end = true;
    }
    else
    {
        player->moveObject(-bg_speed * delta_time, 300 * delta_time);
        if (player->getAnimation()->getPosition().y > bg_ground)
            player->moveObject(0, bg_ground - player->getAnimation()->getPosition().y);
    }
}
void character::updateArrow(float delta_time)
{
    if (col->checkArrow() && arrow_state == "ar_ArrowSpit")
    {
        arrow_state = "ar_ArrowImpact";
        m_data->getSound("arrowHit02")->setVolume(playMusic ? 100 : 0);
        m_data->getSound("arrowHit02")->play();
        arrow->resetAnimation(m_data->getTexture("ar_ArrowImpact"), Vector2i(5, 1), Vector2f(12, 6), 0.1);
    }
    if (arrow_state == "ar_ArrowSpit")
    {
        arrow->moveObject(arrow_direction * character_speed_arrow * delta_time, 0);
        if (arrow->getAnimation()->getPosition().x > screenWidth || arrow->getAnimation()->getPosition().x < -12)
        {
            arrow = nullptr;
            col->delArrow();
        }
    }
    else
    {
        arrow->moveObject(-bg_speed * delta_time, 0);
        arrow->update(delta_time);
        if (arrow->getAnimation()->getCurrentFrame().x == 4)
        {
            arrow = nullptr;
            col->delArrow();
        }
    }
}
void character::update(float delta_time)
{
    time_attack += delta_time;
    if (col->checkCharacter())
        temp_state = "ch_Death";
    if (temp_state == "ch_Death")
        death(delta_time);

    else if ((Keyboard::isKeyPressed(Keyboard::C) || Keyboard::isKeyPressed(Keyboard::S)) && arrow == nullptr && player->getAnimation()->getPosition().y == bg_ground && (time_attack > character_time_attack || state == "ch_Attack"))
        attack(delta_time);
    else
        move(delta_time);
    player->moveObject(-bg_speed * delta_time, 0);
    if (arrow != nullptr)
        updateArrow(delta_time);
    if (player->getAnimation()->getPosition().y > bg_ground)
        player->moveObject(0, bg_ground - player->getAnimation()->getPosition().y);
}
void character::render(RenderWindow *window)
{
    if (!right_direction)
        player->getAnimation()->setScale(-1, 1);
    player->render(window);
    if (arrow != nullptr)
    {
        arrow->getAnimation()->setScale(arrow_direction, 1);
        arrow->render(window);
    }
}