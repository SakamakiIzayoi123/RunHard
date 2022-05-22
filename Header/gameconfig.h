#pragma once
#include <SFML/Graphics.hpp>
#include "../Data/dataManager.h"
#include "collision.h"

#define screenWidth 880
#define screenHeight 495
#define maxFPS 60
#define title "RunHard"
#define showHitBox false
#define showBackground true

// background
#define bg_ground 415 // define is 415
#define bg_speed 100

// monster
#define monster_speed 300
#define monster_speed_poison 600 // velocity of poison
#define monster_time_attack 5    // (s)

// character
#define character_speed 225
#define character_jump_speed 450
#define character_speed_arrow 600
#define character_time_attack 0 // (s)

// creeper
#define creeper_speed 150

sf::RenderWindow *window = new sf::RenderWindow(VideoMode(screenWidth, screenHeight), title, Style::Close);
data_manager *m_data = new data_manager("Data/");
data_manager *bg_data = new data_manager("Data/Background/");
data_manager *bt_data = new data_manager("Data/Button/");
collision *col = new collision;
static float sc;
static bool playMusic = true;