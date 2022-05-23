#pragma once
#include "../GameState/GameState.h"

using namespace sf;

class Application
{
public:
    void Run();
    ~Application();

private:
    void Init();
    void Update(float deltaTime);
    void Render();

private:
    RenderWindow *m_window;
};

Application::~Application()
{
    if (m_window != nullptr)
        delete m_window;
}

void Application::Init()
{
    m_window = window;
    window->setFramerateLimit(maxFPS);
    changeStateMachine.changeState(menu);
    bt_data->addSound("mixkit-video-game-retro-click-237");
}

void Application::Run()
{
    Init();
    Clock clock;
    float deltaTime = 0.f;
    while (m_window->isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        Event event;
        while (m_window->pollEvent(event))
        {
            if (event.type == Event::Closed)
                m_window->close();
        }
        Update(deltaTime);
        Render();
    }
}

void Application::Update(float deltaTime)
{
    // Doing something
    changeStateMachine.performState();
    changeStateMachine.getState()->update(deltaTime);
}

void Application::Render()
{
    m_window->clear(Color::Red);
    // Drawing something
    changeStateMachine.getState()->render(m_window);
    m_window->display();
}
