#include <classes/snake/snake.h>
#include <iostream>

unsigned int Snake::nextSnakeId = 0;

Snake::Snake(AbstractStrategy *newStrategy)
{
    this->strategy = newStrategy->clone();

    this->elements.push_back(sf::Vector2i(0, 0));
    this->elements.push_back(sf::Vector2i(0, 1));
    this->elements.push_back(sf::Vector2i(0, 2));
    this->elements.push_back(sf::Vector2i(0, 3));


    this->id = this->nextSnakeId;
    this->nextSnakeId ++;

    const unsigned int colorsCount = 4;

    sf::Color colors[colorsCount] =
    {
        sf::Color(79, 56, 255),
        sf::Color(255, 66, 239),
        sf::Color(255, 114, 71),
        sf::Color(243, 255, 86)
    };

    this->color = colors[rand() % colorsCount];
}

unsigned int Snake::getId()
{
  return this->id;
}

void Snake::setPosition(sf::Vector2i newPosition)
{
    this->position = newPosition;
}

sf::Vector2i Snake::getPosition()
{
    return this->position;
}

sf::Vector2i Snake::getHead()
{
    return this->elements.front();
}

std::list<sf::Vector2i> Snake::getElements()
{
    return this->elements;
}


void Snake::applyMove(SnakeDirection direction)
{
    sf::Vector2i head = this->elements.front();
    if (direction == SnakeDirection::UP)
        head.y -= 1;
    else if (direction == SnakeDirection::RIGHT)
        head.x += 1;
    else if (direction == SnakeDirection::DOWN)
        head.y += 1;
    else
        head.x -= 1;

    if (!this->isFruit)
    {
        this->elements.pop_back();
    }
    else
    {
        this->hunger = 0;
        this->isFruit = false;
    }

    this->elements.push_front(head);

}

SnakeDirection Snake::exec()
{
    this->hunger ++;

    if (this->hunger >= this->maxHunger)
    {
        this->hunger = 0;
        this->elements.pop_back();
    }

    if (this->elements.size() < 4)
        this->kill();


    return this->strategy->exec();
}

sf::Color Snake::getColor()
{
    return this->color;
}

void Snake::kill()
{
    this->isLive = false;
}

bool Snake::getIsLive()
{
    return this->isLive;
}

void Snake::applyFruit()
{
    this->isFruit = true;
}

AbstractStrategy *Snake::getStrategy()
{
    return this->strategy;
}

bool Snake::canReproduction()
{
    return this->elements.size() > 20;
}

Snake Snake::reproduction()
{

    Snake s(this->strategy);

    s.elements.clear();
    s.setPosition(this->position);

    for (int idx = 0; idx < 10; idx++)
    {
        s.elements.push_back(this->elements.back());
        this->elements.pop_back();
    }


    return s;
}

