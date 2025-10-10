
#include "MapGrass.h"
using namespace sf;

MapGrass::MapGrass () {
    backGround.setSize(Vector2f(5650, 5000));
    if (!texture_window.loadFromFile("images/map2.png")) {
        throw std::runtime_error("Failed to load map.png");
    }
    backGround.setTexture(&texture_window);

    RectangleShape obstacle1(Vector2f(3000, 600));
    obstacle1.setFillColor(Color(255, 0, 0, 0));
    obstacle1.setPosition(1000, 200);

    RectangleShape obstacle2(Vector2f(680, 750));
    obstacle2.setFillColor(Color(0, 255, 0, 0));
    obstacle2.setPosition(1530, 800);

    RectangleShape obstacle3(Vector2f(1150, 700));
    obstacle3.setFillColor(Color(0, 0, 255, 0));
    obstacle3.setPosition(2925, 800);

    RectangleShape obstacle2_1(Vector2f(180, 350));
    obstacle2_1.setFillColor(Color(255, 255, 0, 0));
    obstacle2_1.setPosition(2180, 1150);

    RectangleShape obstacle3_1(Vector2f(220, 275));
    obstacle3_1.setFillColor(Color(255, 0, 255, 0));
    obstacle3_1.setPosition(2710, 1150);

    RectangleShape obstacle4(Vector2f(1150, 900));//blue
    obstacle4.setFillColor(Color(0, 255, 255, 0));//bones
    obstacle4.setPosition(3855, 800);

    RectangleShape obstacle4_1(Vector2f(1150, 500));//blue
    obstacle4_1.setFillColor(Color(0, 255, 255, 0));//bones
    obstacle4_1.setPosition(3855, 1800);

    RectangleShape obstacle4_2(Vector2f(10, 100));//blue
    obstacle4_2.setFillColor(Color(0, 255, 255, 0));//bones
    obstacle4_2.setPosition(4820, 1700);


    RectangleShape obstacle5(Vector2f(300, 3300));
    obstacle5.setFillColor(Color(128, 0, 0, 0));
    obstacle5.setPosition(3570, 2400);


    RectangleShape obstacle6(Vector2f(2200, 300));
    obstacle6.setFillColor(Color(0, 128, 0, 0)); //lava
    obstacle6.setPosition(1400, 4600);

    RectangleShape obstacle7(Vector2f(150, 3300));
    obstacle7.setFillColor(Color(0, 0, 128, 0));
    obstacle7.setPosition(1375, 900);

    RectangleShape obstacle8(Vector2f(350, 1600));//olive
    obstacle8.setFillColor(Color(128, 128, 0, 0));
    obstacle8.setPosition(1375, 3000);

    RectangleShape obstacle9(Vector2f(360, 650));
    obstacle9.setFillColor(Color(128, 0, 128, 0));
    obstacle9.setPosition(1430, 3000);

    RectangleShape obstacle10(Vector2f(300, 380));
    obstacle10.setFillColor(Color(0, 128, 128, 0));
    obstacle10.setPosition(2100, 3100);//br

    RectangleShape obstacle11(Vector2f(550, 380));
    obstacle11.setFillColor(Color(192, 192, 192, 0));
    obstacle11.setPosition(2341, 2438);

    RectangleShape obstacle12(Vector2f(350, 385));
    obstacle12.setFillColor(Color(128, 128, 128, 0));
    obstacle12.setPosition(3241, 2438);

    RectangleShape obstacle13(Vector2f(40, 795));
    obstacle13.setFillColor(Color(255, 192, 203, 0));
    obstacle13.setPosition(2345, 2243);

    RectangleShape obstacle14(Vector2f(43, 590));
    obstacle14.setFillColor(Color(255, 165, 0, 0));
    obstacle14.setPosition(2885, 2443);

    RectangleShape obstacle15(Vector2f(43, 590));
    obstacle15.setFillColor(Color(255, 215, 0, 0));
    obstacle15.setPosition(3210, 2443);

    RectangleShape obstacle15_1(Vector2f(43, 590));
    obstacle15_1.setFillColor(Color(75, 0, 130, 0));
    obstacle15_1.setPosition(2073, 3070);

    RectangleShape obstacle18(Vector2f(680, 43));
    obstacle18.setFillColor(Color(255, 69, 0, 0));
    obstacle18.setPosition(1688, 2220);

    RectangleShape obstacle16(Vector2f(47, 590));
    obstacle16.setFillColor(Color(107, 142, 35, 0));
    obstacle16.setPosition(2345, 1145);

    RectangleShape obstacle17(Vector2f(47, 590));
    obstacle17.setFillColor(Color(75, 0, 130, 0));
    obstacle17.setPosition(2675, 1145);

    RectangleShape obstacle19(Vector2f(700, 100));
    obstacle19.setFillColor(Color(123, 104, 238, 0));
    obstacle19.setPosition(1600, 2800);


    obstacles.push_back(obstacle1);
    obstacles.push_back(obstacle2);
    obstacles.push_back(obstacle3);
    obstacles.push_back(obstacle2_1);
    obstacles.push_back(obstacle3_1);
    obstacles.push_back(obstacle4);
    obstacles.push_back(obstacle5);
    obstacles.push_back(obstacle6);
    obstacles.push_back(obstacle7);
    obstacles.push_back(obstacle8);
    obstacles.push_back(obstacle9);
    obstacles.push_back(obstacle10);
    obstacles.push_back(obstacle11);
    obstacles.push_back(obstacle12);
    obstacles.push_back(obstacle13);
    obstacles.push_back(obstacle14);
    obstacles.push_back(obstacle15);
    obstacles.push_back(obstacle15_1);
    obstacles.push_back(obstacle16);
    obstacles.push_back(obstacle17);
    obstacles.push_back(obstacle18);
    obstacles.push_back(obstacle19);
    obstacles.push_back(obstacle4_1);
    obstacles.push_back(obstacle4_2);

}
        void MapGrass::draw(RenderWindow &window) {
            window.draw(backGround);
            for (const auto &obstacle: obstacles) {
                window.draw(obstacle);
            }
        }








