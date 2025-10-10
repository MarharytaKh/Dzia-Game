#include "FrogMan.h"
using namespace sf;

FrogMan::FrogMan() {
    TextureFrog.loadFromFile("images/frogman.png");
    frog.setTexture(TextureFrog);
    frog.setPosition(4900, 1310);
    frog.setScale(1.2, 1.2);

    T.loadFromFile("images/frogshopBLACK.png");
    black.setTexture(T);
    black.setScale(3.5, 3.5);

    font.loadFromFile("fonts/Adventurer.ttf");
    coin.setFont(font);
    coin.setCharacterSize(55);
    coin.setFillColor(Color(211, 211, 211));

    talk.loadFromFile("images/frog talk.png");
    frogtalk.setTexture(talk);
    frogtalk.setScale(2.0,2.0);
    frogtalk.setPosition(4300, 1210);


    for (int i = 0; i < 8; ++i) {

        itemPurchased[i] = false;
    }
}

void FrogMan::move() {
    f++;
    frog.setTextureRect(IntRect(f / 70 % 8 * 115, 0, 115, 463));
}

void FrogMan::Coins(int phase, std::vector<Enemy>& enemies, const sf::Vector2<float>& mainCharacterPosition, MainCharacter& mainCharacter) {
    coin.setPosition(mainCharacterPosition.x + 665, mainCharacterPosition.y - 470);

    if (phase == 1 && enemies.empty() && !alreadyAdded) {
        money += 15;
        alreadyAdded = true;
    } else if (phase == 2 && enemies.empty() && alreadyAdded) {
        money += 20;
        alreadyAdded = false;
    }

    coin.setString(std::to_string(money));

    if (mainCharacterPosition.x >= 4600  && mainCharacterPosition.y >= 1315 && Keyboard::isKeyPressed(Keyboard::E)) {
        isShopOpen = true;
    }

    if (isShopOpen && Keyboard::isKeyPressed(Keyboard::Q)) {
        isShopOpen = false;
    }

    // Покупка в магазине
    if (isShopOpen && money >= 10) {
        if (Keyboard::isKeyPressed(Keyboard::Num1) && !itemPurchased[0]) {
            money -= 10;
            itemPurchased[0] = true;
            mainCharacter.currentHP += 250;
        } else if (Keyboard::isKeyPressed(Keyboard::Num2) && !itemPurchased[1]) {
            money -= 10;
            itemPurchased[1] = true;
            mainCharacter.currentHP += 250;
        } else if (Keyboard::isKeyPressed(Keyboard::Num3) && !itemPurchased[2]) {
            money -= 10;
            itemPurchased[2] = true;
            mainCharacter.currentHP += 300;
        } else if (Keyboard::isKeyPressed(Keyboard::Num4) && !itemPurchased[3]) {
            money -= 10;
            itemPurchased[3] = true;
            mainCharacter.currentHP += 300;
        }
    }

    if (isShopOpen && money >= 30) {
        if (Keyboard::isKeyPressed(Keyboard::Num5) && !itemPurchased[4]) {
            money -= 30;
            itemPurchased[4] = true;
            mainCharacter.currentHP += 750;
        } else if (Keyboard::isKeyPressed(Keyboard::Num6) && !itemPurchased[5]) {
            money -= 30;
            itemPurchased[5] = true;
            mainCharacter.currentHP += 750;
        } else if (Keyboard::isKeyPressed(Keyboard::Num7) && !itemPurchased[6]) {
            money -= 30;
            itemPurchased[6] = true;
            mainCharacter.currentHP += 800;
        } else if (Keyboard::isKeyPressed(Keyboard::Num8) && !itemPurchased[7]) {
            money -= 30;
            itemPurchased[7] = true;
            mainCharacter.currentHP += 800;
        }
    }

    coin.setString(std::to_string(money));
}

void FrogMan::draw(RenderWindow &window, const sf::Vector2<float>& mainCharacterPosition) {
    window.draw(frog);
    if (!isShopOpen && mainCharacterPosition.x >= 4300  && mainCharacterPosition.y >= 1315){
        window.draw(frogtalk);
    }
}

void FrogMan::draw2(RenderWindow &window, const sf::Vector2<float>& mainCharacterPosition) {
    window.draw(coin);


    Vector2f positions[] = {
            {mainCharacterPosition.x-340,mainCharacterPosition.y+8}, {mainCharacterPosition.x-140,mainCharacterPosition.y+8}, {mainCharacterPosition.x+60,mainCharacterPosition.y+8}, {mainCharacterPosition.x+258,mainCharacterPosition.y+5},
            {mainCharacterPosition.x-338,mainCharacterPosition.y+188}, {mainCharacterPosition.x-140,mainCharacterPosition.y+188}, {mainCharacterPosition.x+60,mainCharacterPosition.y+188}, {mainCharacterPosition.x+258,mainCharacterPosition.y+186}
    };


    for (int i = 0; i < 8; ++i) {
        if (itemPurchased[i]) {
            black.setPosition(positions[i]);
            if(isShopOpen) {
                window.draw(black);
            }
        }
    }
}



