#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include <iostream>

class ControlPanel {
private:
    sf::Texture t1;
    sf::Texture t2;
    sf::Texture t3;
    sf::Texture t4;

    sf::Sprite hp;
    sf::Sprite book;
    sf::Sprite hpEn;
    sf::Sprite dmg;
    sf::Sprite scull;
    sf::Sprite buttons;
    sf::Sprite shop;
    sf::Sprite coin;

    sf::Text countEnemy;
    sf::Text count;
    sf::Text newPhase;

    sf::Font font;
    int f=0;
    bool bookPlaying=true;
    bool isShopOpen=false;
public:

    ControlPanel(sf::Vector2<float> mainCharacterPosition);

    void draw(sf::RenderWindow &window, int phase);

    void update(const sf::Vector2<float> &mainCharacterPosition, int phase);

    void buttons_pict();

    void Scull(int phase);

    void FrogShop(sf::RenderWindow &window, const sf::Vector2<float> &mainCharacterPosition);
};
