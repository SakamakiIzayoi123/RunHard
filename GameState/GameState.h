#pragma once
#include <fstream>
#include "..\Header\button.h"
#include "..\Header\gameconfig.h"
#include <list>
#include "..\Header\Object\character.h"
#include "..\Header\background.h"
#include "..\Header\Object\boss.h"
#include "..\Header\Object\creepManager.h"

using namespace sf;

enum state_type
{
    invalid,
    menu,
    game_play,
    _end,
    setting,
    high_score,
    tutorial
};

class game_state
{
public:
    game_state(){};
    ~game_state(){};
    virtual void init() = 0;
    virtual void update(float delta_time) = 0;
    virtual void render(RenderWindow *window) = 0;
};
class change_state
{
    game_state *state;
    game_state *next_state;

public:
    change_state();
    ~change_state();
    void changeState(game_state *state);
    void changeState(state_type st);
    game_state *getState() { return state; }
    void pushState(game_state *state);
    void pushState(state_type st);
    void performState();
};
change_state changeStateMachine;

class state_menu : public game_state
{
public:
    state_menu(){};
    ~state_menu(){};
    void init();
    void update(float delta_time);
    void render(RenderWindow *window);

private:
    std::vector<button *> m_button;
    Sprite background;
    float time_pressed;
    button *settingButton;
};

/////////////////////////////
class state_play : public game_state
{
public:
    state_play(){};
    ~state_play(){};
    void init();
    void update(float delta_time);
    void render(RenderWindow *window);

private:
    character th;
    boss monster;
    creeper_manager cr;
    Text text;
    background bg[12];
    float time;
};

class state_end : public game_state
{
public:
    state_end(){};
    ~state_end(){};
    void init();
    void update(float delta_time);
    void render(RenderWindow *window);

private:
    std::vector<button *> m_button;
    Sprite background;
    Text text;
};
class state_highScore : public game_state
{
    vector<button *> m_button;
    Text score, tex;
    Sprite background;
    string s;

public:
    state_highScore(){};
    ~state_highScore(){};
    void init();
    void update(float delta_time);
    void render(RenderWindow *window);
};
class state_tutorial : public game_state
{
    Text tex, tut;
    vector<button *> m_button;
    Sprite background;
    string s;

public:
    state_tutorial(){};
    ~state_tutorial(){};
    void init();
    void update(float delta_time);
    void render(RenderWindow *window);
};
void state_tutorial::init()
{
    tex.setString("Tutorial");
    tex.setScale(2, 2);
    tex.setOutlineThickness(2);
    tex.setOutlineColor(Color::Black);
    tex.setFillColor(Color(205, 115, 69));
    tex.setFont(*m_data->getFont("ARCADE.TTF"));
    tex.setPosition(screenWidth / 2 - 100, 70);

    s = "A: run left\nD: run right\nW: jump\nS: attack\nCan double jump.";
    tut.setString(s);
    tut.setOutlineThickness(1);
    tut.setOutlineColor(Color::Black);
    tut.setFillColor(Color::White);
    tut.setFont(*m_data->getFont("ARCADE.TTF"));
    tut.setPosition(screenWidth / 2 - 100, 200);

    button *exitButton = new button;
    exitButton->init();
    exitButton->setAction([]()
                          { changeStateMachine.changeState(menu); });
    exitButton->setPosition(Vector2f(screenWidth - 40, 40));
    exitButton->setTexture(bt_data->getTexture("close"));
    m_button.push_back(exitButton);

    background.setTexture(*bg_data->getTexture("Background"));
    float height = bg_data->getTexture("Background")->getSize().y;
    background.setPosition(Vector2f(0, screenHeight - height));
}
void state_tutorial::update(float delta_time = 0)
{
    for (int i = 0; i < m_button.size(); i++)
        m_button[i]->clickEvent(window);
};
void state_tutorial::render(RenderWindow *window)
{
    window->draw(background);
    for (int i = 0; i < m_button.size(); i++)
        window->draw(*m_button[i]);
    window->draw(tex);
    window->draw(tut);
}

game_state *create(state_type state)
{
    game_state *temp = nullptr;
    switch (state)
    {
    case invalid:
        break;
    case menu:
        temp = new state_menu();
        break;
    case game_play:
        temp = new state_play();
        break;
    case high_score:
        temp = new state_highScore();
        break;
    case tutorial:
        temp = new state_tutorial();
        break;
    default:
        temp = new state_end();
        break;
    }
    return temp;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
change_state::change_state() { next_state = nullptr; };
change_state::~change_state(){};
void change_state::changeState(game_state *state)
{
    next_state = state;
}
void change_state::changeState(state_type st)
{
    game_state *temp = create(st);
    changeState(temp);
}
void change_state::pushState(game_state *state)
{
    next_state = state;
}
void change_state::pushState(state_type st)
{
    game_state *state = create(st);
    pushState(state);
}
void change_state::performState()
{
    if (next_state != nullptr)
    {
        state = next_state;
        state->init();
    }
    next_state = nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void state_menu::init()
{
    time_pressed = 0;

    background.setTexture(*bg_data->getTexture("Background"));
    float height = bg_data->getTexture("Background")->getSize().y;
    background.setPosition(Vector2f(0, screenHeight - height));

    // exit button
    button *exitButton = new button;
    exitButton->init();
    exitButton->setAction([]()
                          { window->close(); });
    exitButton->setPosition(Vector2f(screenWidth / 2 + 90, screenHeight - 80));
    exitButton->setTexture(bt_data->getTexture("close"));
    m_button.push_back(exitButton);

    // play button
    button *playButton = new button;
    playButton->init();
    playButton->setAction([]()
                          { changeStateMachine.changeState(game_play); });
    playButton->setPosition(Vector2f(screenWidth / 2, screenHeight / 2 + 70));
    playButton->setTexture(bt_data->getTexture("play"));
    playButton->setScale(2, 2);
    m_button.push_back(playButton);

    // setting sound button
    settingButton = new button;
    settingButton->init();
    settingButton->setAction([]()
                             { playMusic = playMusic ? false : true; });
    settingButton->setPosition(Vector2f(screenWidth / 2 - 90, screenHeight - 80));
    settingButton->setTexture(bt_data->getTexture(playMusic ? "music" : "music_off"));

    // high score
    button *hScoreButton = new button;
    hScoreButton->init();
    hScoreButton->setAction([]()
                            { changeStateMachine.changeState(high_score); });
    hScoreButton->setPosition(Vector2f(screenWidth / 2 - 30, screenHeight - 80));
    hScoreButton->setTexture(bt_data->getTexture("prize"));
    m_button.push_back(hScoreButton);

    // tutorial button
    button *tutorialButton = new button;
    tutorialButton->init();
    tutorialButton->setAction([]()
                              { changeStateMachine.changeState(tutorial); });
    tutorialButton->setTexture(bt_data->getTexture("faq"));
    tutorialButton->setPosition(Vector2f(screenWidth / 2 + 30, screenHeight - 80));
    m_button.push_back(tutorialButton);
}
void state_menu::update(float delta_time)
{
    time_pressed += delta_time;
    if (time_pressed < 0.5)
        return;
    for (int i = 0; i < m_button.size(); i++)
        m_button[i]->clickEvent(window);
    if (settingButton->isClick(window))
    {
        settingButton->clickEvent(window);
        time_pressed = 0;
    }
    settingButton->setTexture(bt_data->getTexture(playMusic ? "music" : "music_off"));
}
void state_menu::render(RenderWindow *window)
{
    window->draw(background);
    for (int i = 0; i < m_button.size(); i++)
        window->draw(*m_button[i]);
    window->draw(*settingButton);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void state_play::init()
{
    time = 0;
    sc = 0;
    monster.move(-200, 0);
    m_data->getMusic("Uprising")->setVolume(playMusic ? 30 : 0);
    m_data->getMusic("Uprising")->play();
    m_data->getMusic("Uprising")->setLoop(true);
    m_data->getSound("Monster Growl-SoundBible.com-344645592")->setVolume(playMusic ? 20 : 0);
    m_data->getSound("Monster Growl-SoundBible.com-344645592")->play();
    cr.init();
    for (int i = 0; i < 12; i++)
    {
        bg[i].init(to_string(i), bg_speed - i * 5);
    }

    text.setFont(*m_data->getFont("ARCADE.TTF"));
    text.setFillColor(Color::Cyan);
    text.setOutlineThickness(1);
    text.setOutlineColor(Color::Black);
    text.setPosition(30, 30);
}
void state_play::update(float delta_time)
{
    col->update();
    th.update(delta_time);
    if (time > 1.5)
        monster.update(delta_time, th.getPosition());
    else
        time += delta_time;
    cr.update(delta_time);
    sc += delta_time * 2;
    text.setString("Score: " + to_string(int(sc)));
    for (int i = 11; i >= 0; i--)
    {
        bg[i].update(delta_time);
    }
    if (th.isDead())
    {
        changeStateMachine.changeState(_end);
        col->reset();
    }
}
void state_play::render(RenderWindow *window)
{
    for (int i = 11; i >= 0; i--)
    {
        bg[i].render(window);
    }
    cr.render(window);
    monster.render(window);
    th.render(window);
    window->draw(text);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void state_end::init()
{
    m_data->getMusic("Uprising")->stop();

    text.setFillColor(Color::White);
    text.setPosition(screenWidth / 2 - 100, screenHeight / 2 - 50);
    text.setString("Your score: " + to_string(int(sc)));
    text.setFont(*m_data->getFont("ARCADE.TTF"));
    text.setOutlineThickness(1);
    text.setOutlineColor(Color::Black);

    {
        int score[5];
        ifstream infile("Data/hs.txt");
        for (int i = 0; i < 5; i++)
            infile >> score[i];
        for (int i = 0; i < 5; i++)
        {
            if (sc > score[i])
            {
                for (int j = 4; j > i; j--)
                    score[j] = score[j - 1];
                score[i] = sc;
                sc = 0;
                ofstream outfile("Data/hs.txt");
                for (int i = 0; i < 5; i++)
                    outfile << score[i] << " ";
                outfile.close();
            }
        }
        infile.close();
    }

    background.setTexture(*bg_data->getTexture("Background"));
    float height = bg_data->getTexture("Background")->getSize().y;
    background.setPosition(Vector2f(0, screenHeight - height));

    // button
    button *menuButton = new button;
    menuButton->init();
    menuButton->setPosition(Vector2f(screenWidth / 2 + 35, screenHeight / 2 + 75));
    menuButton->setAction([]()
                          { changeStateMachine.changeState(menu); });
    menuButton->setTexture(bt_data->getTexture("menu"));
    m_button.push_back(menuButton);

    button *playAgain = new button;
    playAgain->init();
    playAgain->setPosition(Vector2f(screenWidth / 2 - 35, screenHeight / 2 + 75));
    playAgain->setAction([]()
                         { changeStateMachine.changeState(game_play); });
    playAgain->setTexture(bt_data->getTexture("restart"));
    m_button.push_back(playAgain);
};
void state_end::update(float delta_time)
{
    for (int i = 0; i < m_button.size(); i++)
        m_button[i]->clickEvent(window);
}
void state_end::render(RenderWindow *window)
{
    window->draw(background);
    for (int i = 0; i < m_button.size(); i++)
        window->draw(*m_button[i]);
    window->draw(text);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void state_highScore::init()
{
    background.setTexture(*bg_data->getTexture("Background"));
    float height = bg_data->getTexture("Background")->getSize().y;
    background.setPosition(Vector2f(0, screenHeight - height));

    ifstream input("Data/hs.txt");
    input >> s;
    for (int i = 0; i < 4; i++)
    {
        string temp;
        input >> temp;
        s += '\n' + temp;
    }
    input.close();

    score.setFont(*m_data->getFont("ARCADE.TTF"));
    score.setString(s);
    score.setFillColor(Color::White);
    score.setPosition(screenWidth / 2, 200);
    score.setOutlineThickness(1);
    score.setOutlineColor(Color::Black);

    tex.setFont(*m_data->getFont("ARCADE.TTF"));
    tex.setString("High Score");
    tex.setFillColor(Color::White);
    tex.setPosition(screenWidth / 2 - 200, 50);
    tex.setCharacterSize(50);
    tex.setOutlineThickness(3);
    tex.setOutlineColor(Color::Black);
    tex.setScale(2, 2);

    button *exitButton = new button;
    exitButton->init();
    exitButton->setAction([]()
                          { changeStateMachine.changeState(menu); });
    exitButton->setPosition(Vector2f(screenWidth - 40, 40));
    exitButton->setTexture(bt_data->getTexture("close"));
    m_button.push_back(exitButton);
};
void state_highScore::update(float delta_time)
{
    for (int i = 0; i < m_button.size(); i++)
        m_button[i]->clickEvent(window);
}
void state_highScore::render(RenderWindow *window)
{
    window->draw(background);
    for (int i = 0; i < m_button.size(); i++)
        window->draw(*m_button[i]);
    window->draw(score);
    window->draw(tex);
}