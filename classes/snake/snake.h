#ifndef SNAKE_H
#define SNAKE_H

#include <classes/snake/strategies/abstract_strategy.h>
#include <SFML/Graphics.hpp>
#include <list>

class Snake
{
public:
    unsigned int getId();

    static unsigned int nextSnakeId;
    void setPosition(sf::Vector2i newPosition);
    sf::Vector2i getPosition();
    std::list<sf::Vector2i> getElements();
    sf::Vector2i getHead();
    Snake(AbstractStrategy *newStrategy);

    SnakeDirection exec();
    void applyMove(SnakeDirection direction);
    void applyFruit();

    void kill();
    bool getIsLive();
private:
    unsigned int id;
    AbstractStrategy *strategy;
    std::list<sf::Vector2i> elements;
    sf::Vector2i position;
    bool isLive = true;
    bool isFruit = false;
};

#endif
