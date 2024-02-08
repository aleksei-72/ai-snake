#include <classes/render_manager.h>

RenderManager::RenderManager(sf::Vector2i wSize)
{
    this->windowSize = wSize;
}

void RenderManager::init()
{
    this->window = new sf::RenderWindow(
        sf::VideoMode(this->windowSize.x, this->windowSize.y),
        "Hello World"
    );
    if (this->frameRate) {
        this->window->setFramerateLimit(*this->frameRate);
    } else {
        this->window->setVerticalSyncEnabled(true);
    }
}

bool RenderManager::isTerminated()
{
    return !this->window->isOpen();
}

void RenderManager::startDraw()
{
    sf::Event event;

    while (this->window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            this->window->close();

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                this->window->close();
            }

            if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
            {
                ManualStrategy::currentDirection = SnakeDirection::UP;
            }
            else if (event.key.code ==  sf::Keyboard::D || event.key.code == sf::Keyboard::Right)
            {
                ManualStrategy::currentDirection = SnakeDirection::RIGHT;
            }
            else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
            {
                ManualStrategy::currentDirection = SnakeDirection::DOWN;
            }
            else if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)
            {
                ManualStrategy::currentDirection = SnakeDirection::LEFT;
            }
        }
    }

    this->window->clear();
}

void RenderManager::endDraw()
{
    this->window->display();
}

void RenderManager::setFrameRate(unsigned int *frameRate)
{
    this->frameRate = frameRate;
}

void RenderManager::draw(const sf::Drawable& drawable)
{
    this->window->draw(drawable);
}

sf::Vector2u RenderManager::getWindowSize()
{
    this->window->getSize();
}
