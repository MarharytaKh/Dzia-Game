#include "GameMenu.h"

//I made a system for selecting items and highlighting them in a different color by using the up-down keys based on this video:
//https://www.youtube.com/watch?v=sA4EakzDBw4&t=1567s
void game::GameMenu::setInitText(sf::Text& text, sf::String str, float xpos, float ypos) {
    text.setFont(font);
    text.setFillColor(menu_text_color);
    text.setString(str);
    text.setCharacterSize(size_font);
    text.setPosition(xpos, ypos);
}
void game::GameMenu::AlignMenu(int posx)
{
    float nullx = 0;
    for (int i = 0; i < 1; i++) {
        mainMenu[i].setPosition(mainMenu[i].getPosition().x - nullx, mainMenu[i].getPosition().y);
    }

}

game::GameMenu::GameMenu(sf::RenderWindow& window, float menux, float menuy, std::vector<sf::String> name, int sizeFont, int step)
        :mywindow(window), menu_X(menux), menu_Y(menuy), size_font(sizeFont), menu_Step(step)
{

    if (!font.loadFromFile("fonts/Adventurer.ttf")) exit(32);
    max_menu = name.size();
    mainMenu = new sf::Text[max_menu];

    for (int i = 0, ypos = menu_Y; i < max_menu; i++, ypos += menu_Step) setInitText(mainMenu[i], name[i], menu_X, ypos);
    mainMenuSelected = 0;
    mainMenu[mainMenuSelected].setFillColor(chose_text_color);
}

void game::GameMenu::MoveUp()
{
    mainMenuSelected--;

    if (mainMenuSelected >= 0) {
        mainMenu[mainMenuSelected].setFillColor(chose_text_color);
        mainMenu[mainMenuSelected + 1].setFillColor(menu_text_color);
    }
    else
    {
        mainMenu[0].setFillColor(menu_text_color);
        mainMenuSelected = max_menu - 1;
        mainMenu[mainMenuSelected].setFillColor(chose_text_color);
    }
}

void game::GameMenu::MoveDown()
{
    mainMenuSelected++;

    if (mainMenuSelected < max_menu) {
        mainMenu[mainMenuSelected - 1].setFillColor(menu_text_color);
        mainMenu[mainMenuSelected].setFillColor(chose_text_color);
    }
    else
    {
        mainMenu[max_menu - 1].setFillColor(menu_text_color);
        mainMenuSelected = 0;
        mainMenu[mainMenuSelected].setFillColor(chose_text_color);
    }

}
void game::GameMenu::draw()
{
    for (int i = 0; i < max_menu; i++) mywindow.draw(mainMenu[i]);
}

