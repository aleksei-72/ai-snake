#ifndef GAME_H
#define GAME_H

#include <classes/snake/snake.h>
#include <classes/map.h>
#include <vector>
#include <classes/render_manager.h>
#include <classes/snake/strategies/ai_strategy.h>

class Game
{
public:
    Game();
    void addSnake(Snake newSnake);
    void setMap(Map *newMap);
    void setRenderManager(RenderManager *render);
    void setFrameRate(int newFrameRate);
    void init();
    void run();
private:

    void exec(sf::Int64 t);
    void updateSnake(std::vector<Snake>::iterator snake);
    void draw();
    std::vector<Snake> snakes;

    int snakesCount = 0;
    Map *map;

    int frameRate;
    RenderManager *render;

    sf::Clock timer;
};

#endif
