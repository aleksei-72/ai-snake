#include <iostream>
#include <classes/game.h>
#include <classes/snake/snake.h>
#include <classes/snake/strategies/ai_strategy.h>
#include <classes/snake/strategies/manual_strategy.h>
#include <classes/map.h>
#include <ctime>

using namespace std;

int main()
{
    srand(time(0));
    Game game;

    Map map(100, 75);
    map.generateRandom();

    game.setMap(&map);

    //ManualStrategy *manualStrategy = new ManualStrategy();


    AiStrategy *aiStrategy = new AiStrategy();

    for (int i: {0, /*1, 2, 3, 4, 5, 7, 8, 9, 10, 11, 12, 13, 14*/})
    {
        aiStrategy->initSensivity();
        Snake snake1(aiStrategy);
        snake1.setPosition(sf::Vector2i(30 + i*5, 30));
        game.addSnake(snake1);
    }



    RenderManager render(sf::Vector2i(800, 600));

    unsigned int frameRate = 144;
    render.setFrameRate(&frameRate);

    render.init();

    game.setRenderManager(&render);
    game.init();
    game.run();

    cout << "Hello World!" << endl;
    return 0;
}
