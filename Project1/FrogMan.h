#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "MainCharacter.h"
#pragma once
class FrogMan {
private:
    sf::Texture TextureFrog;
    sf::Texture T;
    sf::Texture talk;
    sf::Sprite frog;
    sf::Sprite black;
    sf::Sprite frogtalk;

    sf::Font font;
    sf::Text coin;
    int money=5;
    bool alreadyAdded=false;
    bool isShopOpen=false;
    bool itemPurchased[8];

    bool stop=false;


    int f=0;

public:
    FrogMan();
    auto move()->void;
    void Coins(int phase, std::vector<Enemy>& enemies, const sf::Vector2<float>& mainCharacterPosition, MainCharacter& mainCharacter );
    void draw(sf::RenderWindow &window, const sf::Vector2<float>& mainCharacterPosition);
    void draw2(sf::RenderWindow &window, const sf::Vector2<float>& mainCharacterPosition);
};


