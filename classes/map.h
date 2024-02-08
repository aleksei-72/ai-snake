#ifndef MAP_H
#define MAP_H

#include <SFML/System/Vector2.hpp>
#include <random>
#include <vector>

class Map
{
public:
    Map(int width, int height);
    void generateRandom();
    void generateFruit(unsigned idx);

    sf::Vector2u getMapSize();
    std::vector<sf::Vector2i> getBlocks();

    std::vector<sf::Vector2i> getBorderBlocks();
    std::vector<sf::Vector2i> getFruits();
private:
    std::vector<sf::Vector2i> blocks;
    std::vector<sf::Vector2i> borderBlocks;
    int width, height;
    std::vector<sf::Vector2i> fruits;

    float filling = 0.01;
    int fruitsCount = 350;
};

#endif
