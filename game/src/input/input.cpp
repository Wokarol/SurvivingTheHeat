#include <input.h>
#include <SFML/Graphics.hpp>
#include <console.h>

struct DirectionKey
{
    bool pressed;
    sf::Keyboard::Key code;
    sf::Vector2f direction;

    DirectionKey(sf::Keyboard::Key key, sf::Vector2f direction) :
        pressed(false),
        code(key), direction(direction)
    {}
};

std::vector<DirectionKey> directionKeys{
    { sf::Keyboard::A, sf::Vector2f(-1, 0) },
    { sf::Keyboard::D, sf::Vector2f(1, 0) },
    { sf::Keyboard::W, sf::Vector2f(0, -1) },
    { sf::Keyboard::S, sf::Vector2f(0,  1) },
};

void wok::input::resetKeyStateBeforeTheFrame()
{
    input::attack.resetSingleFrameData();
}

void wok::input::handleInputKeysPressed(const sf::Event& event)
{
    for (auto& key : directionKeys)
    {
        if (!key.pressed && event.key.code == key.code)
        {
            movement += key.direction;
            key.pressed = true;
        }
    }
}

void wok::input::handleInputKeysReleased(const sf::Event& event)
{
    for (auto& key : directionKeys)
    {
        if (key.pressed && event.key.code == key.code)
        {
            movement -= key.direction;
            key.pressed = false;
        }
    }
}

void wok::input::handleMouseButtonsPressed(const sf::Event& event)
{
    attack.checkForKeyPressed(event.mouseButton.button);
}

void wok::input::handleMouseButtonsReleased(const sf::Event& event)
{
    attack.checkForKeyReleased(event.mouseButton.button);
}
