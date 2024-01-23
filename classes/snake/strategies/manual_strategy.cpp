#include <classes/snake/strategies/manual_strategy.h>

SnakeDirection ManualStrategy::currentDirection = SnakeDirection::UP;


SnakeDirection ManualStrategy::exec()
{
    this->lastDirection = this->currentDirection;
    return this->lastDirection;
}
