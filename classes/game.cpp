#include <classes/game.h>
#include <iostream>


Game::Game()
{

}

void Game::setRenderManager(RenderManager *render)
{
    this->render = render;
}

void Game::addSnake(Snake newSnake)
{
    this->snakes.push_back(newSnake);
}

void Game::setMap(Map *newMap)
{
    this->map = newMap;
}

void Game::setFrameRate(int newFrameRate)
{
    this->frameRate = newFrameRate;
}

void Game::init()
{

}

void Game::run()
{
    this->timer.restart();

    while (!this->render->isTerminated()) {
        this->exec(this->timer.getElapsedTime().asMicroseconds());
        this->render->startDraw();
        this->draw();
        this->render->endDraw();
        this->timer.restart();
    }
}

void Game::updateSnake(std::vector<Snake>::iterator snake)
{
    sf::Vector2u mapSize = this->map->getMapSize();

    SnakeDirection direction = snake->exec();
    snake->applyMove(direction);

    sf::Vector2i pos(
        snake->getHead().x + snake->getPosition().x,
        snake->getHead().y + snake->getPosition().y
    );

    if (pos.x < 0 || pos.x >= (int)mapSize.x || pos.y < 0 || pos.y >= (int)mapSize.y)
    {
        snake->kill();
        return;
    }

    if (
        this->map->getFruit().x == snake->getHead().x + snake->getPosition().x &&
        this->map->getFruit().y == snake->getHead().y + snake->getPosition().y
    )
    {
       snake->applyFruit();
       this->map->generateFruit();
    }

    for (sf::Vector2i item: this->map->getBlocks())
    {
        if (item.x == pos.x && item.y == pos.y)
        {
            snake->kill();
            return;
        }
    }

    for (std::vector<Snake>::iterator snakeIt = this->snakes.begin(); snakeIt != this->snakes.end(); ++snakeIt)
    {
        if (!snakeIt->getIsLive()) {
            continue;
        }

        unsigned int snakeItElementIdx = 0;

        for (sf::Vector2i snakeItElementPos: snakeIt->getElements())
        {
            snakeItElementIdx ++;

            unsigned int snakeElementIdx = 0;
            for(sf::Vector2i snakeElementPos: snake->getElements())
            {
                snakeElementIdx ++;

                // проверять только столкновение голов с телами и головами, не проверять столкновение тел
                if (snakeItElementIdx != 1 && snakeElementIdx != 1)
                    continue;


                if (
                    snakeItElementPos.x + snakeIt->getPosition().x  == snakeElementPos.x + snake->getPosition().x &&
                    snakeItElementPos.y + snakeIt->getPosition().y == snakeElementPos.y + snake->getPosition().y
                ) {
                    if (
                        snake->getId() == snakeIt->getId() &&
                        snakeItElementIdx == snakeElementIdx
                    )
                    {
                        continue;
                    }

                    if (snakeItElementIdx == 1)
                        snake->kill();

                    if (snakeElementIdx == 1)
                        snakeIt->kill();

                    continue;
                }
            }
        }
    }

}

void Game::exec(sf::Int64 t)
{
    for (std::vector<Snake>::iterator snakeIt = this->snakes.begin(); snakeIt != this->snakes.end(); ++snakeIt)
    {
        if (!snakeIt->getIsLive()) {
            continue;
        }

        this->updateSnake(snakeIt);
    }

}

void Game::draw()
{
    sf::Vector2u windowSize = this->render->getWindowSize();
    sf::Vector2u mapSize = this->map->getMapSize();

    sf::Vector2f unit = sf::Vector2f(
        windowSize.x / (float)mapSize.x,
        windowSize.y / (float)mapSize.y
    );

    sf::VertexArray renderUnit(sf::Quads, 4);

    // render map
    renderUnit[0].position = sf::Vector2f(0.f, 0.f);
    renderUnit[1].position = sf::Vector2f(unit.x, 0.f);
    renderUnit[2].position = sf::Vector2f(unit.x, unit.y);
    renderUnit[3].position = sf::Vector2f(0.f, unit.y);

    for (int i: {0, 1, 2, 3})
        renderUnit[i].color = sf::Color(158, 60, 0);


    for (sf::Vector2i item: this->map->getBlocks())
    {
        sf::VertexArray renderItem = renderUnit;
        for (int i: {0, 1, 2, 3})
        {
            renderItem[i].position.x += item.x * unit.x;
            renderItem[i].position.y += item.y * unit.y;
        }


        this->render->draw(renderItem);
    }

    // render snakes
    for (int i: {0, 1, 2, 3})
        renderUnit[i].color = sf::Color(0, 38, 255);

    for (Snake snake: this->snakes)
    {
        if (!snake.getIsLive())
            continue;

        for (sf::Vector2i item: snake.getElements())
        {
            sf::VertexArray renderItem = renderUnit;
            for (int i: {0, 1, 2, 3})
            {
                renderItem[i].position.x += (snake.getPosition().x + item.x) * unit.x;
                renderItem[i].position.y += (snake.getPosition().y + item.y) * unit.y;
            }

            this->render->draw(renderItem);
        }
    }

    // render fruit
    for (int i: {0, 1, 2, 3})
        renderUnit[i].color = sf::Color(76, 255, 0);
    {
        sf::VertexArray renderItem = renderUnit;
        for (int i: {0, 1, 2, 3})
        {
            renderItem[i].position.x += this->map->getFruit().x * unit.x;
            renderItem[i].position.y += this->map->getFruit().y * unit.y;
        }

        this->render->draw(renderItem);
    }

}
