#include <classes/snake/strategies/manual_strategy.h>

SnakeDirection ManualStrategy::currentDirection = SnakeDirection::UP;


AbstractStrategy *ManualStrategy::clone()
{
    ManualStrategy *a = new ManualStrategy();

    return a;
}

SnakeDirection ManualStrategy::exec()
{
    this->lastDirection = this->currentDirection;
    return this->lastDirection;
}

StrategyType ManualStrategy::getType()
{
    return StrategyType::MANUAL;
}
