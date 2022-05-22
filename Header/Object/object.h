#pragma once
#include "animation.h"
#include "hitBox.h"

using namespace sf;

class object
{
    animation *ani;
    hitBox *hb;

public:
    object(Texture *texture, Vector2i frameNum, Vector2i position, Vector2i size, Vector2f origin, bool lastFrame);
    object();
    void update(float deltaTime);
    void render(RenderWindow *window);
    void resetAnimation(Texture *texture, Vector2i frameNum, Vector2f origin, float frameTime, bool lastFrame);
    animation *getAnimation() { return ani; }
    hitBox *getHitBox() { return hb; }
    void moveObject(float x, float y);
};

object::object(Texture *texture, Vector2i frameNum, Vector2i position, Vector2i size, Vector2f origin, bool lastFrame = true)
{
    ani = new animation(*texture, frameNum, 0.1, lastFrame);
    ani->setPosition(position.x, position.y);
    ani->setOrigin(origin);
    hb = new hitBox(size, position);
}
void object::update(float deltaTime)
{
    ani->update(deltaTime);
}
void object::render(RenderWindow *window)
{
    if (showHitBox && hb != nullptr)
        hb->render(window);
    window->draw(*ani);
}
void object::resetAnimation(Texture *texture, Vector2i frameNum, Vector2f origin, float frameTime = 0.05, bool lastFrame = true)
{
    Vector2i position = Vector2i(ani->getPosition().x, ani->getPosition().y);
    ani = new animation(*texture, frameNum, frameTime, lastFrame);
    ani->setPosition(position.x, position.y);
    ani->setOrigin(origin);
}
void object::moveObject(float x, float y)
{
    ani->move(x, y);
    hb->setPosition(ani->getPosition().x, ani->getPosition().y);
}