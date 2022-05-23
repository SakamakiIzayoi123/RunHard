#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class animation : public Sprite
{
public:
    animation(const Texture &texture, Vector2i frameNum, float frameTime, bool lastFrame);
    void update(float deltaTime);
    Vector2i getCurrentFrame();
    Vector2i getFrameNum();

private:
    Vector2i frameNum;
    Vector2i currentFrame;

    float frameTime;
    float currentTime;

    Vector2i rectSize;
    Vector2i rectUV;

    IntRect rect;
    int numberOfFrames;
    int frame_num;

    void calculatorRectSize();
    void calculatorRectUV();
    void applyRect();
    void changeFrame();
};

animation::animation(const Texture &texture, Vector2i _frameNum, float _frameTime, bool lastFrame = true)
{
    this->setTexture(texture);
    frameNum = _frameNum;
    frameTime = _frameTime;
    currentFrame = Vector2i(0, 0);
    currentTime = 0;
    frame_num = 0;
    if (lastFrame)
        numberOfFrames = frameNum.x * frameNum.y;
    else
        numberOfFrames = frameNum.x * frameNum.y - 1;
    calculatorRectSize();
    applyRect();
}
void animation::update(float deltaTime)
{
    currentTime += deltaTime;
    if (currentTime >= frameTime)
    {
        currentFrame.x++;

        // change the current frame
        changeFrame();

        // apply the change
        calculatorRectUV();
        applyRect();

        // update the currentTime
        currentTime -= frameTime;
    }
}

void animation::calculatorRectSize()
{
    rectSize.x = this->getTexture()->getSize().x / frameNum.x;
    rectSize.y = this->getTexture()->getSize().y / frameNum.y;
}
void animation::calculatorRectUV()
{
    rectUV.x = currentFrame.x * rectSize.x;
    rectUV.y = currentFrame.y * rectSize.y;
}
void animation::applyRect()
{
    rect = IntRect(rectUV, rectSize);
    this->setTextureRect(rect);
}
void animation::changeFrame()
{
    frame_num++;
    if (frame_num == numberOfFrames)
        frame_num = 0;
    currentFrame.y = frame_num / frameNum.x;
    currentFrame.x = frame_num % frameNum.x;
}
Vector2i animation::getCurrentFrame()
{
    return currentFrame;
}
Vector2i animation::getFrameNum()
{
    return frameNum;
}