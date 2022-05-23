#pragma once
#include <SFML/Graphics.hpp>
#include "Object/hitBox.h"

using namespace sf;
using namespace std;

bool checkCollision(hitBox *a, hitBox *b);

class collision
{
    hitBox *character, *boss, *poison, *arrow, *temp;
    vector<hitBox *> creep;

    bool check_character, check_boss, check_poison, check_arrow;
    vector<bool> check_creep;

    bool _checkCharacter();
    bool _checkBoss();
    bool _checkArrow();
    bool _checkPoison();
    bool _checkCreeper(int n);

public:
    collision();
    ~collision() { reset(); };
    void setCharacter(hitBox *_character) { this->character = _character; }

    void setBoss(hitBox *_boss) { this->boss = _boss; }
    void setPoison(hitBox *_poison) { this->poison = _poison; }
    void setArrow(hitBox *_arrow) { arrow = _arrow; }
    void setTemp(hitBox *_temp) { temp = _temp; }
    int addCreeper(hitBox *_creeper);
    void addCreeper(int n, hitBox *_creeper)
    {
        creep[n] = _creeper;
        check_creep[n] = false;
    }
    hitBox *getCharacter() { return this->character; }
    hitBox *getArrow() { return this->arrow; }
    void delTemp() { temp = nullptr; }
    void delArrow() { arrow = nullptr; }
    void delPoison() { poison = nullptr; }
    void delCharacter() { character = nullptr; }
    void delCreeper(int n) { creep[n] = nullptr; }
    bool checkCharacter() { return check_character; }
    bool checkBoss() { return check_boss; }
    bool checkArrow() { return check_arrow; }
    bool checkPoison() { return check_poison; }
    bool checkCreeper(int n) { return check_creep[n]; }
    void update();
    void reset();
};
collision::collision()
{
    character = nullptr;
    boss = nullptr;
    poison = nullptr;
}
void collision::reset()
{
    character = nullptr;
    boss = nullptr;
    poison = nullptr;
    arrow = nullptr;
    for (int i = creep.size(); i > 0; i--)
    {
        creep.pop_back();
    }
}
int collision::addCreeper(hitBox *_creeper)
{
    creep.push_back(_creeper);
    check_creep.push_back(false);
    return creep.size() - 1;
}
bool collision::_checkCharacter()
{
    if (checkCollision(character, boss))
        return true;
    if (checkCollision(character, temp))
        return true;
    if (checkCollision(character, poison))
        return true;
    for (int i = 0; i < creep.size(); i++)
    {
        if (checkCollision(character, creep[i]))
            return true;
    }
    return false;
}
bool collision::_checkBoss()
{
    if (checkCollision(arrow, boss))
        return true;
    return false;
}
void collision::update()
{
    check_character = _checkCharacter();
    check_boss = _checkBoss();
    check_arrow = _checkArrow();
    check_poison = _checkPoison();
    for (int i = 0; i < creep.size(); i++)
    {
        check_creep[i] = _checkCreeper(i);
    }
}
bool collision::_checkArrow()
{
    if (checkCollision(arrow, boss))
        return true;
    if (checkCollision(arrow, temp))
        return true;
    for (int i = 0; i < creep.size(); i++)
    {
        if (checkCollision(arrow, creep[i]))
            return true;
    }
    return false;
}
bool collision::_checkPoison()
{
    if (checkCollision(poison, character))
        return true;
    for (int i = 0; i < creep.size(); i++)
    {
        if (checkCollision(poison, creep[i]))
            return true;
    }
    return false;
}
bool collision::_checkCreeper(int n)
{
    if (checkCollision(creep[n], arrow))
        return true;
    if (checkCollision(creep[n], boss))
        return true;
    if (checkCollision(creep[n], poison))
        return true;
    return false;
}
bool checkCollision(hitBox *a, hitBox *b)
{
    if (a == nullptr || b == nullptr)
    {
        return false;
    }
    if (a->getGlobalBounds().intersects(b->getGlobalBounds()))
        return true;
    return false;
}
