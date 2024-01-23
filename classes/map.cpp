#include <classes/map.h>

Map::Map(int width, int height)
{
    this->width = width;
    this->height = height;
}

void Map::updateFruitPosition()
{
    this->fruit = sf::Vector2i(rand()/this->width, rand()/this->height);
}

sf::Vector2i Map::getFruit()
{
    return this->fruit;
}

void Map::generateFruit()
{
    this->fruit = sf::Vector2i(rand()%this->width, rand()%this->height);
}

void Map::generateRandom()
{
    int blocksCount = this->width * this->height * this->filling;

    this->blocks.clear();

    for (int i = 0; i < blocksCount; i++)
    {
        sf::Vector2i v(rand()%this->width, rand()%this->height);
        this->blocks.push_back(v);
    }

    this->fruit = sf::Vector2i(rand()%this->width, rand()%this->height);
}

sf::Vector2u Map::getMapSize()
{
    return sf::Vector2u(width, height);
}

std::vector<sf::Vector2i> Map::getBlocks()
{
    return this->blocks;
}
