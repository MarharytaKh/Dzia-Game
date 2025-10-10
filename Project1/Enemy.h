#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <string>
#include <stdexcept>
#include "MainCharacter.h"

class MainCharacter;
enum class EnemyType {
    jellyfish, dragon, boss
};

class Enemy {
private:
    sf::Texture te;
    sf::Sprite enemy;
    sf::Vector2f direction;
    float speed;
    float patrolMin;
    float patrolMax;
    int f = 0;
    int T = 220;
    sf::RectangleShape Hp;
    float maxHP = 1000;
    float X=0;
    float Y=0;
    float factorX=2.0f;
    float factorY=2.0f;
    float posX=80;
    float posY=30;


    int bT=0;

    void setTexture(const std::string& texturePath);

public:
    Enemy(EnemyType type, const sf::Vector2f &startPos, float patrolMin, float patrolMax);
    void update(std::vector<Enemy>& enemies, sf::Vector2<float> mainCharacterPosition, float detectionRadius, float MainCharacterDmg);
    void draw(sf::RenderWindow &window) const;
    float getPositionX();
    float getPositionY();
    static std::vector<Enemy> createEnemies(int phase);
    float currentHP = maxHP;
    static std::vector<sf::Texture> textures;

    int bss=7;

    sf::Vector2f getPosition() const;


    float damage;
};


