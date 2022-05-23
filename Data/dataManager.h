#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <utility>

using namespace sf;
using namespace std;

class data_manager
{
public:
    data_manager(string path);
    ~data_manager();

    Texture *getTexture(string name);
    void addTexture(string name);
    void removeTexture(string name);

    Font *getFont(string name);
    void addFont(string name);
    void removeFont(string name);

    Sound *getSound(string name);
    void addSound(string name);
    void removeSound(string name);

    Music *getMusic(string name);
    void addMusic(string name);
    void removeMusic(string name);

private:
    map<string, Texture *> mapTextures;
    map<string, Font *> mapFonts;
    map<string, Sound *> mapSounds;
    map<string, Music *> mapMusics;

    string texturePath;
    string fontPath;
    string soundPath;
};

data_manager::data_manager(string path)
{
    texturePath = path + "Texture/";
    fontPath = path + "Font/";
    soundPath = path + "Sound/";
}
data_manager::~data_manager()
{
    for (auto it : mapTextures)
        if (it.second != NULL)
            delete it.second;
    mapTextures.clear();

    for (auto it : mapFonts)
        if (it.second != NULL)
            delete it.second;
    mapFonts.clear();

    for (auto it : mapSounds)
        if (it.second != NULL)
            delete it.second;
    mapSounds.clear();
}
void data_manager::addTexture(string name)
{
    map<string, Texture *>::iterator it = mapTextures.find(name);
    if (it != mapTextures.end())
        return;
    Texture *texture = new Texture;
    texture->loadFromFile(texturePath + name + ".png");
    mapTextures.insert(pair<string, Texture *>(name, texture));
}
void data_manager::removeTexture(string name)
{
    map<string, Texture *>::iterator it = mapTextures.find(name);
    if (it == mapTextures.end())
        return;
    if (it->second != NULL)
        mapTextures.erase(it);
}
Texture *data_manager::getTexture(string name)
{
    map<string, Texture *>::iterator it = mapTextures.find(name);
    if (it != mapTextures.end())
        return it->second;
    addTexture(name);
    return getTexture(name);
}

void data_manager::addFont(string name)
{
    map<string, Font *>::iterator it = mapFonts.find(name);
    if (it != mapFonts.end())
        return;
    Font *font = new Font;
    font->loadFromFile(fontPath + name);

    mapFonts.insert(pair<string, Font *>(name, font));
}
void data_manager::removeFont(string name)
{
    map<string, Font *>::iterator it = mapFonts.find(name);
    if (it == mapFonts.end())
        return;
    mapFonts.erase(it);
}
Font *data_manager::getFont(string name)
{
    map<string, Font *>::iterator it = mapFonts.find(name);
    if (it != mapFonts.end())
        return it->second;
    addFont(name);
    return getFont(name);
}

void data_manager::addSound(string name)
{
    map<string, Sound *>::iterator it = mapSounds.find(name);
    if (it != mapSounds.end())
        return;
    SoundBuffer *buffer = new SoundBuffer;
    buffer->loadFromFile(soundPath + name + ".wav");
    Sound *sound = new Sound;
    sound->setBuffer(*buffer);

    mapSounds.insert(pair<string, Sound *>(name, sound));
}
void data_manager::removeSound(string name)
{
    map<string, Sound *>::iterator it = mapSounds.find(name);
    if (it == mapSounds.end())
        return;
    mapSounds.erase(it);
}
Sound *data_manager::getSound(string name)
{
    map<string, Sound *>::iterator it = mapSounds.find(name);
    if (it != mapSounds.end())
        return it->second;
    addSound(name);
    return getSound(name);
}

void data_manager::addMusic(string name)
{
    map<string, Music *>::iterator it = mapMusics.find(name);
    if (it != mapMusics.end())
        return;
    Music *music = new Music;
    music->openFromFile(soundPath + name + ".wav");

    mapMusics.insert(pair<string, Music *>(name, music));
}
void data_manager::removeMusic(string name)
{
    map<string, Music *>::iterator it = mapMusics.find(name);
    if (it == mapMusics.end())
        return;
    mapMusics.erase(it);
}
Music *data_manager::getMusic(string name)
{
    map<string, Music *>::iterator it = mapMusics.find(name);
    if (it != mapMusics.end())
        return it->second;
    addMusic(name);
    return getMusic(name);
}