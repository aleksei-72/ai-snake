#ifndef AI_STRATEGY_H
#define AI_STRATEGY_H

#include <classes/snake/strategies/abstract_strategy.h>
#include <SFML/System/Vector2.hpp>
#include <map>
#include <list>
#include <vector>
#include <random>

class AiStrategy: public AbstractStrategy
{
public:
    AiStrategy();
    void clearMap();
    void mapSnake(sf::Vector2i position, std::list<sf::Vector2i> elements);
    void mapThisSnake(sf::Vector2i position, std::list<sf::Vector2i> elements);
    void mapWall(std::vector<sf::Vector2i> elements);
    void mapFruits(std::vector<sf::Vector2i> elements);
    void setPosition(sf::Vector2i position);
    void initSensivity();
    void mutate();
    SnakeDirection exec() override;
    StrategyType getType() override;
    AbstractStrategy *clone() override;
private:
    int generation = 0;
    int viewRadius = 15;
    std::map<int, std::map<int, char>> view;
    std::map<char, std::map<int, std::map<int, std::map<SnakeDirection, float>>>> sensitivity;

    sf::Vector2i position;
};

#endif
