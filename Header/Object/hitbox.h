#pragma once
#include "../gameconfig.h"

using namespace sf;

class hitBox : public RectangleShape
{
    Vector2i size;
    Vector2i position;
    int hp = 1;

public:
    hitBox(Vector2i size, Vector2i position);
    void render(RenderWindow *window);
};

hitBox::hitBox(Vector2i size, Vector2i position)
{
    this->size = size;
    this->position = position;
    this->setPosition(position.x, position.y);
    this->setSize(Vector2f(size.x, size.y));
    this->setOutlineThickness(1);
    this->setOutlineColor(Color::Red);
    this->setOrigin(Vector2f(size.x / 2, size.y / 2));
}
void hitBox::render(RenderWindow *window)
{
    window->draw(*this);
}