#include <iostream>
#include "Enemy.h"
using namespace sf;
//animation for main character, enemies, attacks, etc.:
//https://www.youtube.com/watch?v=OhseDhZ6ZvY
std::vector<sf::Texture> Enemy::textures;

void Enemy::setTexture(const std::string& texturePath) {
    if (!te.loadFromFile(texturePath)) {
        throw std::runtime_error("Failed to load texture for enemy");
    }
    enemy.setTexture(te);
}

Enemy::Enemy(EnemyType type, const Vector2f& startPos, float patrolMin, float patrolMax)
        : patrolMin(patrolMin), patrolMax(patrolMax) {
    std::string texturePath;

    Hp.setSize(sf::Vector2f(X, 10));
    Hp.setFillColor(sf::Color(178, 34, 34));

    switch (type) {
        case EnemyType::dragon:
            texturePath = "images/dragon.png";
            speed = 0.3f;
            direction = { -1, 0 };
            maxHP = 1200;
            X = 400;
            Y = 5;
            damage = 1.7;
            break;

        case EnemyType::jellyfish:
            texturePath = "images/jellyfish.png";
            speed = 0.1f;
            direction = { -1, 0 };
            maxHP = 1000;
            damage = 1.0;
            X = 200;
            Y = 5;
            break;

        case EnemyType::boss:
            texturePath = "images/boss.png";
            speed = 0.5f;
            direction = { -1, 0 };
            maxHP = 6000;
            X = 800;
            Y = 10;
            damage = 1.3;
            factorX = 3.0;
            factorY = 3.0;
            bss = 9;
            posX = -300;
            posY = 700;
            break;

        default:
            throw std::invalid_argument("Unknown enemy type");
    }

    currentHP = maxHP;
    setTexture(texturePath);

    enemy.setScale(factorX, factorY);
    enemy.setPosition(startPos);
}

void Enemy::update(std::vector<Enemy>& enemies, Vector2<float> mainCharacterPosition, float detectionRadius, float MainCharacterDmg) {
    Vector2f currentPos = enemy.getPosition();
    f++;
    float dx = mainCharacterPosition.x - currentPos.x + posX;
    float dy = mainCharacterPosition.y - currentPos.y - posY;
    float distance = std::sqrt(dx * dx + dy * dy);

    if (distance < detectionRadius) {
        Vector2f unitDirection(dx / distance, dy / distance);
        enemy.move(unitDirection * speed);

        if (bss == 9) {
            enemy.setTextureRect(sf::IntRect(f / 100 % 12 * 410, 581, 410, 363));
        } else {
            enemy.setTextureRect(sf::IntRect(f / 100 % 6 * 252, 435, 253, 210));
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            currentHP -= MainCharacterDmg;
            Hp.setSize(sf::Vector2f((float)currentHP / maxHP * X, 10));

            if (currentHP<=0){

            }

        }
    } else {

        enemy.move(direction * speed);

        if (currentPos.x < patrolMin) {
            direction.x = 1;
            T = 0;
            bT = 0;
        } else if (currentPos.x > patrolMax) {
            direction.x = -1;
            T = 201;
            bT = 298;
        }
        f++;
        if (bss == 9) {
            enemy.setTextureRect(sf::IntRect(f / 100 % 5 * 289, bT, 289, 298));
        } else {
            enemy.setTextureRect(sf::IntRect(f / 160 % 5 * 239, T, 239, 201));
        }
    }


    if (bss==9){
        Hp.setPosition(mainCharacterPosition.x-450, mainCharacterPosition.y-500);
    }
    else {
        Hp.setPosition(getPositionX()+100, getPositionY() - 40);
    }
}

void Enemy::draw(RenderWindow &window) const {
    window.draw(enemy);
    window.draw(Hp);
}

float Enemy::getPositionX() {
    return enemy.getPosition().x;
}

float Enemy::getPositionY() {
    return enemy.getPosition().y;
}

Vector2f Enemy::getPosition() const {
    return enemy.getPosition();
}

std::vector<Enemy> Enemy::createEnemies(int phase) {
    std::vector<Enemy> enemies;
    if (textures.empty()) {

        sf::Texture dragonTexture;
        if (!dragonTexture.loadFromFile("images/dragon.png")) {
            throw std::runtime_error("Failed to load texture for dragon");
        }
        textures.push_back(dragonTexture);

        sf::Texture goblinTexture;
        if (!goblinTexture.loadFromFile("images/jellyfish.png")) {
            throw std::runtime_error("Failed to load texture for goblin");
        }
        textures.push_back(goblinTexture);

        sf::Texture bossTexture;
        if (!bossTexture.loadFromFile("images/boss.png")) {
            throw std::runtime_error("Failed to load texture for boss");
        }
        textures.push_back(bossTexture);
    }

    switch (phase) {
        case 1:

            enemies.emplace_back(EnemyType::jellyfish, sf::Vector2f(2500, 1450), 2300, 2700);
            enemies.back().enemy.setTexture(textures[1]);

            enemies.emplace_back(EnemyType::jellyfish, sf::Vector2f(2700, 2750), 2300, 2700);
            enemies.back().enemy.setTexture(textures[1]);

            enemies.emplace_back(EnemyType::jellyfish, sf::Vector2f(2000, 4050), 2300, 2700);
            enemies.back().enemy.setTexture(textures[1]);

            break;
        case 2:

            enemies.emplace_back(EnemyType::dragon, sf::Vector2f(2500, 1450), 2300, 2700);
            enemies.back().enemy.setTexture(textures[0]);

            enemies.emplace_back(EnemyType::dragon, sf::Vector2f(2700, 2900), 2300, 2700);
            enemies.back().enemy.setTexture(textures[0]);

            enemies.emplace_back(EnemyType::dragon, sf::Vector2f(2000, 4050), 2300, 2700);
            enemies.back().enemy.setTexture(textures[0]);

            break;
        case 3:

            enemies.emplace_back(EnemyType::boss, sf::Vector2f(2100, 2550), 2300, 2700);
            enemies.back().enemy.setTexture(textures[2]);
            break;
        default:

            break;
    }
    return enemies;
}

