#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "ControlPanel.h"
class MainCharacter{
private:

    sf::RectangleShape HitBox;
    sf::Texture t1;
    sf::Texture t2;
    sf::Texture t3;
    sf::Sprite s1;
    sf::Sprite attak;
    sf::Sprite fr;
    float distance;
    int f = 0;
    int k=0;
    sf::RectangleShape Hp;
    sf::Vector2f lastPosition;
    int maxHP = 8000;

public:

    MainCharacter();
    auto move()->void;
    auto getBottom() -> sf::Rect<float>;
    auto draw(sf::RenderWindow &window)->void;
    auto scales(sf::RenderWindow &window)->void;
    auto moveBack()->void;
    auto getPositionX() -> float;
    auto getPositionY() -> float;
    auto lava(sf::RenderWindow &window)->void;
    auto DMG()->void;
    sf::RectangleShape Dmg;
    int currentHP = maxHP;
    int currentDmg=2;
    void Attak();



    void HP(sf::Vector2<float> enemyPosition, float detectionRadius, float damage, int bss);
    sf::Vector2f getPosition() const;
    bool isDead();
    void setPosition(float heroX, float heroY);
};
