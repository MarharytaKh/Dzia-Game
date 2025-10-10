#pragma once
#include <SFML/Graphics.hpp>
#include "SFML/Audio/SoundBuffer.hpp"
//CONSTRUCTOR OF THE MENU
namespace game {
    class GameMenu
    {
        float menu_X;
        float menu_Y;
        int menu_Step;
        int max_menu;
        int size_font;
        int mainMenuSelected;
        sf::Font font;
        sf::Text* mainMenu;

        sf::Color menu_text_color=sf::Color(211, 211, 211);
        sf::Color chose_text_color=sf::Color(178, 34, 34);

        //SETTINGS MENU TEXT
        void setInitText(sf::Text& text, sf::String str, float xpos, float ypos);

        sf::RenderWindow& mywindow;

    public:
        GameMenu(sf::RenderWindow& window, float menux, float menuy, std::vector<sf::String> name, int sizeFont=40, int step=60);

        void draw();
        void MoveUp();
        void MoveDown();
        void AlignMenu(int posx);


        int getSelectedMenuNumber()
        {
            return mainMenuSelected;
        }


    };

}
