#ifndef MANUAL_STRATEGY_H
#define MANUAL_STRATEGY_H

#include <classes/snake/strategies/abstract_strategy.h>

class ManualStrategy: public AbstractStrategy
{
public:
    static SnakeDirection currentDirection;
    SnakeDirection exec() override;
    StrategyType getType() override;
    AbstractStrategy *clone() override;
private:
    SnakeDirection lastDirection = SnakeDirection::UP;
};

#endif
