#include <classes/snake/snake.h>

unsigned int Snake::nextSnakeId = 0;

Snake::Snake(AbstractStrategy *newStrategy)
{
    this->strategy = newStrategy;

    this->elements.push_back(sf::Vector2i(0, 0));
    this->elements.push_back(sf::Vector2i(0, 1));
    this->elements.push_back(sf::Vector2i(0, 2));
        this->elements.push_back(sf::Vector2i(0, 3));
        this->elements.push_back(sf::Vector2i(0, 4));
        /*this->elements.push_back(sf::Vector2i(0, 5));
            this->elements.push_back(sf::Vector2i(0, 6));
            this->elements.push_back(sf::Vector2i(0, 7));
            this->elements.push_back(sf::Vector2i(0, 8));
            this->elements.push_back(sf::Vector2i(0, 9));
            this->elements.push_back(sf::Vector2i(0, 10));
            this->elements.push_back(sf::Vector2i(0, 11));
            this->elements.push_back(sf::Vector2i(0, 12));*/


    this->id = this->nextSnakeId;
    this->nextSnakeId ++;
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
        this->isFruit = false;
    }

    this->elements.push_front(head);

}

SnakeDirection Snake::exec()
{
    return this->strategy->exec();
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

