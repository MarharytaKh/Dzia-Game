#pragma once
#include <SFML/Graphics.hpp>

class MapGrass {
private:
sf::RectangleShape backGround;
sf::Texture texture_window;
std::vector<sf::RectangleShape> obstacles;
public:
    MapGrass();
    auto draw(sf::RenderWindow &window)->void;

    const std::vector<sf::RectangleShape> &getObstacles() {
        return obstacles;
    }
};