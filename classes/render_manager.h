#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <classes/snake/strategies/manual_strategy.h>

class RenderManager
{
public:
    RenderManager(sf::Vector2i wSize);
    void init();
    void setFrameRate(unsigned int *frameRate);
    void startDraw();
    void endDraw();
    bool isTerminated();
    void draw(const sf::Drawable& drawable);
    sf::Vector2u getWindowSize();
private:
    sf::Vector2i windowSize;
    sf::RenderWindow *window;
    unsigned int *frameRate = nullptr;
};

#endif
