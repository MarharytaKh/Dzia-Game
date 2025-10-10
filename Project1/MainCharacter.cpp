
#include "MainCharacter.h"
//animation for main character, enemies, attacks, etc.:
//https://www.youtube.com/watch?v=OhseDhZ6ZvY
using namespace sf;

   MainCharacter::MainCharacter() {
       Hp.setSize(sf::Vector2f(715, 29));
       Hp.setFillColor(Color(107, 142, 35));

       Dmg.setSize(sf::Vector2f(35, 100));
       Dmg.setFillColor(Color(25, 25, 112));

         t1.loadFromFile("images/maincharacter2.png");

         s1.setTexture(t1);
         s1.setTextureRect(IntRect(0, 0, 69, 72));
         s1.setScale(2.8f, 2.8f);
         s1.setPosition(2450, 900);
         lastPosition = s1.getPosition();

       t2.loadFromFile("images/small_slash_2.png");
       attak.setTexture(t2);

       t3.loadFromFile("images/maincharacter2fire.png");
       fr.setTexture(t3);

     }

     void MainCharacter::move() {
         lastPosition = s1.getPosition();
         f++;
        Attak();

         if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)
                 ) {
             s1.setTextureRect(sf::IntRect(f / 50 % 4 * 69, 0, 69, 75));
             s1.move(0, 0.6);
             if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
                 s1.move(0, 1.0);
             }
         }
         if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)
                 ) {
             s1.setTextureRect(sf::IntRect(f / 50 % 4 * 69, 76, 69, 70));
             s1.move(0, -0.6);
             if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
                 s1.move(0, -1.0);
             }
         }
         if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)
                 ) {
             s1.setTextureRect(sf::IntRect(f / 50 % 12 * 69, 146, 69, 70));
             s1.move(0.6, 0);
             if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
                 s1.move(1.0, 0);
             }

         }
         if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)
                 ) {
             s1.setTextureRect(sf::IntRect(f / 50 % 12 * 69, 216, 69, 70));
             s1.move(-0.6, 0);
             if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
                 s1.move(-1.0, 0);
             }


         }
         Hp.setPosition(s1.getPosition().x - 500, s1.getPosition().y + 425);
         Dmg.setPosition(s1.getPosition().x - 870, s1.getPosition().y-80);
         fr.setPosition(s1.getPosition().x+35,s1.getPosition().y-120);

     }


     auto MainCharacter::getBottom() -> Rect<float> {

         HitBox.setSize(Vector2f (100.0, 20.0));
         HitBox.setFillColor(Color(200, 255, 0, 256));  // 200
         HitBox.setPosition(getPositionX()+40, getPositionY() + 140);
         return HitBox.getGlobalBounds();

     }

     void MainCharacter::draw(RenderWindow &window) {
         window.draw(s1);
         window.draw(HitBox);
         if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
             window.draw(attak);
         };



     }
     void MainCharacter::scales(RenderWindow &window){
       window.draw(Hp);
         window.draw(Dmg);
   }

     void MainCharacter::moveBack() {
         s1.setPosition(lastPosition);
     }

void MainCharacter::Attak(){
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        f++;
        attak.setTextureRect(sf::IntRect(f / 30 % 4 * 92, 0, 92, 67));
        attak.setScale(3.0f, 3.0f);
        attak.setPosition(getPositionX()+60, getPositionY()+70);

    }
}
         auto MainCharacter::getPositionX() -> float {
             return s1.getPosition().x;
         }
         auto MainCharacter::getPositionY() -> float {
             return s1.getPosition().y;
         }
        Vector2f MainCharacter::getPosition() const {
         return s1.getPosition();
         }

void MainCharacter::HP(Vector2<float> enemyPosition, float detectionRadius, float damage, int bss){
    Vector2f currentPos = s1.getPosition();
    if(bss==9) {
        float dx = enemyPosition.x - currentPos.x;
        float dy = enemyPosition.y + 400 - currentPos.y;
         distance = std::sqrt(dx * dx + (dy + 400) * dy);
        detectionRadius+=400;
    }
    else{float dx = enemyPosition.x - currentPos.x;
        float dy = enemyPosition.y + - currentPos.y;
         distance = std::sqrt(dx * dx + dy * dy);}

    if (distance < detectionRadius ) {
        currentHP-=damage;
        Hp.setSize(sf::Vector2f((float)currentHP / maxHP * 715, 29));
        f++;
        if(currentHP<=20){

                s1.setTextureRect(sf::IntRect(f / 18 % 8 * 70, 364, 69, 72));
                f++;
            currentHP=0;
        }
    }
}


void MainCharacter::DMG(){
currentDmg+=currentDmg*0.9f;
        Dmg.setSize(sf::Vector2f( 35, 200));

}
bool MainCharacter::isDead(){
       if (currentHP<=0){
           return true;
       }
       else return false;
   }

void MainCharacter::setPosition(float heroX, float heroY){
       s1.setPosition(heroX, heroY);
   }
void MainCharacter::lava(RenderWindow &window){
    if (s1.getPosition().y>=4100){
        currentHP-=0.5;
        Hp.setSize(sf::Vector2f((float)currentHP / maxHP * 715, 29));

        f++;
        fr.setTextureRect(sf::IntRect(f / 40 % 2 * 115, 0, 115, 168));
        window.draw(fr);
    }


}








