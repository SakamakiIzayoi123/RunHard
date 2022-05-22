#pragma once
#include "gameconfig.h"

using namespace sf;

class button : public RectangleShape
{
public:
    button() { mouseClick = false; }
    ~button(){};

    void init();
    bool isClick(RenderWindow *window);
    void clickEvent(RenderWindow *window);
    void setAction(void (*action)()) { func = action; }

private:
    void (*func)();
    bool mouseClick;
};

void button::init()
{
    this->setSize(Vector2f(50, 50));
    this->setOrigin(this->getSize() / 2.f);
}

bool button::isClick(RenderWindow *window)
{
    if (Mouse::isButtonPressed(Mouse::Left) && this->getGlobalBounds().contains((Vector2f)Mouse::getPosition(*window)))
        return true;
    return false;
}
void button::clickEvent(RenderWindow *window)
{
    if (isClick(window))
    {
        func();
        if (bt_data->getSound("mixkit-video-game-retro-click-237")->getStatus() != SoundSource::Playing)
        {
            bt_data->getSound("mixkit-video-game-retro-click-237")->setVolume(playMusic ? 100 : 0);
            bt_data->getSound("mixkit-video-game-retro-click-237")->play();
        }
    }
}
