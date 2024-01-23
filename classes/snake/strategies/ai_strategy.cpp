#include <classes/snake/strategies/ai_strategy.h>
#include <iostream>
#include <cmath>

AiStrategy::AiStrategy()
{
    for (int x = -this->viewRadius; x < this->viewRadius; x++)
    {
        for (int y = -this->viewRadius; y < this->viewRadius; y++)
        {

            if (x == 0 && y == 0)
                continue;

            for (char type: {'s', 'w', 'f', 'c', 'n'})
            {
                float dist = sqrt(x*x + y*y);

                if (dist < 2 && (type == 's' || type == 'w' || type == 'c'))
                {
                    float force = 50;

                    if (type == 'c')
                        force = 40;


                    std::list<SnakeDirection> directions;

                    if (x < 0)
                        directions.push_back(SnakeDirection::LEFT);

                    if (x > 0)
                        directions.push_back(SnakeDirection::RIGHT);

                    if (y < 0)
                        directions.push_back(SnakeDirection::UP);

                    if (y > 0)
                        directions.push_back(SnakeDirection::DOWN);

                    for (SnakeDirection dir: directions)
                        this->sensitivity[type][x][y][dir] = -(force / dist);
                }

                if ( dist < 10 && (type == 'f' || type == 'n'))
                {
                    float force = 200;
                    if (type == 'n')
                        force = 2;

                    std::list<SnakeDirection> directions;
                    if (x < 0)
                        directions.push_back(SnakeDirection::LEFT);

                    if (x > 0)
                        directions.push_back(SnakeDirection::RIGHT);

                    if (y < 0)
                        directions.push_back(SnakeDirection::UP);

                    if (y > 0)
                        directions.push_back(SnakeDirection::DOWN);

                    for (SnakeDirection dir: directions)
                        this->sensitivity[type][x][y][dir] = force / dist;
                }
            }
        }
    }
}

void AiStrategy::mapSnake(sf::Vector2i position, std::list<sf::Vector2i> elements)
{
    for (sf::Vector2i i: elements)
    {
        this->view[position.x + i.x - this->position.x][position.y + i.y - this->position.y] = 's';
    }
}

void AiStrategy::mapThisSnake(sf::Vector2i position, std::list<sf::Vector2i> elements)
{
    for (sf::Vector2i i: elements)
    {
        this->view[position.x + i.x - this->position.x][position.y + i.y - this->position.y] = 'c';
    }
}

void AiStrategy::mapWall(std::vector<sf::Vector2i> elements)
{
    for (sf::Vector2i i: elements)
    {
        this->view[i.x - this->position.x][i.y - this->position.y] = 'w';
    }
}

void AiStrategy::mapFruits(std::vector<sf::Vector2i> elements)
{
    for (sf::Vector2i i: elements)
    {
        this->view[i.x - this->position.x][i.y - this->position.y] = 'f';
    }
}

void AiStrategy::setPosition(sf::Vector2i position)
{
    this->position = position;
}

SnakeDirection AiStrategy::exec()
{

    std::map<SnakeDirection, float> result;
    result[SnakeDirection::UP] = 0;
    result[SnakeDirection::RIGHT] = 0;
    result[SnakeDirection::DOWN] = 0;
    result[SnakeDirection::LEFT] = 0;


    for (int x = -this->viewRadius; x < this->viewRadius; x++)
    {
        for (int y = -this->viewRadius; y < this->viewRadius; y++)
        {
            char type = this->view[x][y];
            std::map<SnakeDirection, float> effect = this->sensitivity[type][x][y];

            for (auto item: effect)
            {
                result[item.first] += item.second;
            }

        }
     }

    std::vector<SnakeDirection> maxDirections;

    for(auto item: result)
    {
        if (!maxDirections.size() || result[item.first] == result[maxDirections.front()])
        {
            maxDirections.push_back(item.first);
        }

        if (!maxDirections.size() || result[item.first] > result[maxDirections.front()])
        {
            maxDirections.clear();
            maxDirections.push_back(item.first);
        }
    }

    return maxDirections.at(rand() % maxDirections.size());
}

void AiStrategy::clearMap()
{
    for (int x = -this->viewRadius; x < this->viewRadius; x++)
    {
        for (int y = -this->viewRadius; y < this->viewRadius; y++)
        {
            this->view[x][y] = 'n';
        }
    }
}

StrategyType AiStrategy::getType()
{
    return StrategyType::AI;
}
