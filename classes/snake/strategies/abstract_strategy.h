#ifndef ABSTRACT_STRATEGY_H
#define ABSTRACT_STRATEGY_H

#include <classes/snake/snake_directions.h>
#include <classes/snake/strategies/strategy_type.h>

class AbstractStrategy
{
public:
    virtual SnakeDirection exec() = 0;
    virtual StrategyType getType() = 0;
    virtual AbstractStrategy *clone() = 0;
private:

};

#endif
