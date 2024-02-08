#include <classes/map.h>

Map::Map(int width, int height)
{
    this->width = width;
    this->height = height;


    for (int x = -1; x <= (int)this->getMapSize().x; x++)
    {
        this->borderBlocks.push_back(sf::Vector2i(x, -1));
        this->borderBlocks.push_back(sf::Vector2i(x, this->getMapSize().y));

        if (x == -1 || x == (int)this->getMapSize().x)
        {
            for (int y = -1; y <= (int)this->getMapSize().y; y++)
            {
                this->borderBlocks.push_back(sf::Vector2i(x, y));
            }
        }
    }
}

std::vector<sf::Vector2i> Map::getFruits()
{
    return this->fruits;
}

void Map::generateFruit(unsigned int idx)
{
    sf::Vector2i newPos(rand()%this->width, rand()%this->height);
    for (sf::Vector2i item: this->blocks)
    {
        if (item.x == newPos.x && item.y == newPos.y)
        {
            this->generateFruit(idx);
            return;
        }
    }

    this->fruits.at(idx) = newPos;
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

    for(int i = 0; i < this->fruitsCount; i++)
    {
        this->fruits.push_back(sf::Vector2i(0, 0));
        this->generateFruit(i);
    }
}

sf::Vector2u Map::getMapSize()
{
    return sf::Vector2u(width, height);
}

std::vector<sf::Vector2i> Map::getBlocks()
{
    return this->blocks;
}

std::vector<sf::Vector2i> Map::getBorderBlocks()
{
    return this->borderBlocks;
}
