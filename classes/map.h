#ifndef MAP_H
#define MAP_H

#include <SFML/System/Vector2.hpp>
#include <random>
#include <vector>

class Map
{
public:
    Map(int width, int height);
    void updateFruitPosition();
    void generateRandom();
    void generateFruit();

    sf::Vector2u getMapSize();
    std::vector<sf::Vector2i> getBlocks();
    sf::Vector2i getFruit();
private:
    std::vector<sf::Vector2i> blocks;
    int width, height;
    sf::Vector2i fruit;

    float filling = 0.04;
};

#endif
