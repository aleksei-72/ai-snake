#include <iostream>
#include <classes/game.h>
#include <classes/snake/snake.h>
#include <classes/snake/strategies/ai_strategy.h>
#include <classes/snake/strategies/manual_strategy.h>
#include <classes/map.h>

using namespace std;

int main()
{
    Game game;

    Map map(20, 15);
    map.generateRandom();

    game.setMap(&map);

    ManualStrategy *manualStrategy = new ManualStrategy();
    //AiStrategy *aiStrategy = new AiStrategy();

    Snake snake1(manualStrategy);
    snake1.setPosition(sf::Vector2i(11, 12));
    game.addSnake(snake1);

    Snake snake2(manualStrategy);
    snake2.setPosition(sf::Vector2i(9, 12));
    //game.addSnake(snake2);


    RenderManager render;

    unsigned int frameRate = 4;
    render.setFrameRate(&frameRate);

    render.init();

    game.setRenderManager(&render);
    game.init();
    game.run();

    cout << "Hello World!" << endl;
    return 0;
}
