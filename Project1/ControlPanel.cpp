
#include <iostream>
#include "ControlPanel.h"
using namespace sf;
ControlPanel::ControlPanel(Vector2<float> mainCharacterPosition) {
    t1.loadFromFile("images/panel.png");
    t2.loadFromFile("images/book_startOfGame.png");
    t3.loadFromFile("images/frogshop.png");
    t4.loadFromFile("images/coin.png");

    hp.setTexture(t1);
    hp.setTextureRect(IntRect(0, 0, 415, 161));
    hp.setScale(2.0f,1.7f);

    hpEn.setTexture(t1);
    hpEn.setTextureRect(IntRect(23, 117, 585, 64));
    hpEn.setScale(1.5f,1.0f);

    dmg.setTexture(t1);
    dmg.setTextureRect(IntRect(651,70,120,282));
    dmg.setScale(1.7f,1.6f);

    buttons.setTexture(t1);
    buttons.setTextureRect(IntRect(0,343,154,123));
    buttons.setScale(1.7f,1.6f);

    scull.setTexture(t1);
    scull.setTextureRect(IntRect(500,25,107,80) );
    scull.setScale(1.2f,1.2f);

    shop.setTexture(t3);
    shop.setTextureRect(IntRect(0,0,600,338));
    shop.setScale(3.4,3.4);

    coin.setTexture(t4);
    coin.setTextureRect(IntRect(0,0,90,60));
    coin.setScale(2.3,2.4);

    if (!font.loadFromFile("fonts/Adventurer.ttf")) return;

    countEnemy.setFont(font);
    countEnemy.setFillColor(Color(211, 211, 211));
    countEnemy.setCharacterSize(50);

    book.setTexture(t2);
    book.setScale(2.6f, 2.6f);

}

void ControlPanel::buttons_pict() {
    f++;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)
            ) {
        buttons.setTextureRect(sf::IntRect(154, 345, 152, 131));

    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)
            ) {
        buttons.setTextureRect(sf::IntRect(308, 345, 152, 131));

    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)
            ) {
        buttons.setTextureRect(sf::IntRect(465, 345, 154, 131));

    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)
            ) {
        buttons.setTextureRect(sf::IntRect(625, 345, 152, 131));

    }
    else {buttons.setTextureRect(sf::IntRect(0,343,154,131));}
}
void ControlPanel::Scull(int phase){
    if (phase==1){
        countEnemy.setString("3 jellyfishes");
    }
    else if(phase==2){
        countEnemy.setString("3 baby dragons");
    }
    else {countEnemy.setString("");
    }
}


void ControlPanel::update(const sf::Vector2<float>& mainCharacterPosition, int phase) {
    hp.setPosition(mainCharacterPosition.x - 550, mainCharacterPosition.y + 350);
    dmg.setPosition(mainCharacterPosition.x - 950, mainCharacterPosition.y-240);
    buttons.setPosition(mainCharacterPosition.x - 850, mainCharacterPosition.y+230);
    book.setPosition(mainCharacterPosition.x-700, mainCharacterPosition.y-600);
    shop.setPosition(mainCharacterPosition.x-1000,mainCharacterPosition.y-600);
    coin.setPosition(mainCharacterPosition.x+650, mainCharacterPosition.y-500);
    if (f / 18 < 4) {
        book.setTextureRect(sf::IntRect(f / 30 % 4 * 555, 0, 555, 450));
        f++;
    } else {

        book.setTextureRect(sf::IntRect(3 * 555, 0, 555, 450));
        if (bookPlaying && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            bookPlaying = false;
        }
    }
                    if (phase<3) {
                        scull.setPosition(mainCharacterPosition.x - 950, mainCharacterPosition.y - 450);
                        countEnemy.setPosition(mainCharacterPosition.x - 800, mainCharacterPosition.y - 450);
                    }
                    else if (phase==3){
                        hpEn.setPosition(mainCharacterPosition.x-470, mainCharacterPosition.y-538);
                    };


}

void ControlPanel::draw(RenderWindow &window, int phase) {

    window.draw(hp);
    window.draw(dmg);
    window.draw(buttons);
    if (phase<3) {
        window.draw(scull);
        window.draw(countEnemy);
    }
    else if(phase==3){
        window.draw(hpEn);
    }
    if (bookPlaying) {
        window.draw(book);
    }

}

void ControlPanel::FrogShop(sf::RenderWindow &window, const sf::Vector2<float>& mainCharacterPosition){

    if (mainCharacterPosition.x>= 4600 && mainCharacterPosition.x<=4900 && mainCharacterPosition.y>=1315 && (Keyboard::isKeyPressed(sf::Keyboard::E))){
        isShopOpen=true;
    }
    if ( isShopOpen){
        window.draw(shop);
    }
    if (isShopOpen && sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        isShopOpen = false;
    }
    window.draw(coin);

}
