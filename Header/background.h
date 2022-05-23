#pragma once
#include "gameconfig.h"

using namespace sf;

class background
{
public:
    void init(std::string name, int m_speed);
    void update(float deltaTime);
    void render(RenderWindow *window);

private:
    Vector2i sizeImage;
    Sprite image1;
    Sprite image2;
    float speed;
};

//============================================================================
void background::init(std::string name, int m_speed)
{
    image1.setTexture(*bg_data->getTexture(name));
    image2.setTexture(*bg_data->getTexture(name));

    sizeImage = (Vector2i)bg_data->getTexture(name)->getSize();

    image1.setPosition(0, screenHeight - sizeImage.y);
    image2.setPosition(sizeImage.x, screenHeight - sizeImage.y);
    speed = m_speed;
}
void background::update(float deltaTime)
{
    image1.move(-speed * deltaTime, 0);
    image2.move(-speed * deltaTime, 0);
    if (image1.getPosition().x < -sizeImage.x)
        image1.setPosition(sizeImage.x + image2.getPosition().x, image1.getPosition().y);
    if (image2.getPosition().x < -sizeImage.x)
        image2.setPosition(sizeImage.x + image1.getPosition().x, image2.getPosition().y);
}
void background::render(RenderWindow *window)
{
    window->draw(image1);
    window->draw(image2);
}

void setBackground();