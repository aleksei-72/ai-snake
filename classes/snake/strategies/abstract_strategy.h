#ifndef ABSTRACT_STRATEGY_H
#define ABSTRACT_STRATEGY_H

#include <classes/snake/snake_directions.h>

class AbstractStrategy
{
public:
    virtual SnakeDirection exec() = 0;
private:

};

#endif
