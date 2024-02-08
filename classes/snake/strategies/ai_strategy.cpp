#include <classes/snake/strategies/ai_strategy.h>
#include <iostream>
#include <cmath>

AbstractStrategy *AiStrategy::clone()
{
    AiStrategy *a = new AiStrategy();
    a->sensitivity = this->sensitivity;
    a->mutate();
    a->generation = this->generation + 1;

    std::cout << "new AI generation: " << a->generation << '\n';

    return static_cast<AbstractStrategy*>(a);
}

void AiStrategy::initSensivity()
{
    for (int x = -this->viewRadius; x < this->viewRadius; x++)
    {
        for (int y = -this->viewRadius; y < this->viewRadius; y++)
        {

            if (x == 0 && y == 0)
                continue;

            for (char type: {'s', 'w', 'f', 'c'})
            {
                float dist = sqrt(x*x + y*y);
                float force = 0;

                if (dist < 3 && (type == 's' || type == 'w' || type == 'c'))
                {
                    force = -190;
                }

                if ( dist < 8 && type == 'f')
                {
                    force = 100;
                }


                if (x < 0)
                {
                    this->sensitivity[type][x][y][SnakeDirection::LEFT] = (force / (abs(x) * dist));
                }

                if (x > 0)
                {
                    this->sensitivity[type][x][y][SnakeDirection::RIGHT] = (force / (abs(x) * dist));
                }

                if (y < 0)
                {
                    this->sensitivity[type][x][y][SnakeDirection::UP] = (force / (abs(y) * dist));
                }

                if (y > 0)
                {
                    this->sensitivity[type][x][y][SnakeDirection::DOWN] = (force / (abs(y) * dist));
                }

            }
        }
    }
}

AiStrategy::AiStrategy()
{

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
            this->view[x][y] = ' ';
        }
    }
}

void AiStrategy::mutate()
{
    float mutateProbability = 0.05;
    float mutateForce = 10.f;

    for (int x = -this->viewRadius; x < this->viewRadius; x++)
    {
        for (int y = -this->viewRadius; y < this->viewRadius; y++)
        {

            if (x == 0 && y == 0)
                continue;

            if ((float)(rand() % 100000) / 100000 > mutateProbability)
                continue;

            char c[5] = {'s', 'w', 'f', 'c'};

            this->sensitivity[c[rand() % 5]][x][y][SnakeDirection::LEFT] += (float)(rand() % 30 - 15) / 15.f * mutateForce;
            this->sensitivity[c[rand() % 5]][x][y][SnakeDirection::RIGHT] += (float)(rand() % 30 - 15) / 15.f * mutateForce;
            this->sensitivity[c[rand() % 5]][x][y][SnakeDirection::UP] += (float)(rand() % 30 - 15) / 15.f * mutateForce;
            this->sensitivity[c[rand() % 5]][x][y][SnakeDirection::DOWN] += (float)(rand() % 30 - 15) / 15.f * mutateForce;

        }
    }
}

StrategyType AiStrategy::getType()
{
    return StrategyType::AI;
}
