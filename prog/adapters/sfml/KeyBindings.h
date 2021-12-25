#ifndef GAME_KEYBINDINGS_H
#define GAME_KEYBINDINGS_H

#include <SFML/Window/Keyboard.hpp>

enum class Key {
    UNDEFINED,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    ACTION,
    RESTART,
    FULLSCREEN,
    EXIT
};

class KeyBindings {
public:
    static Key getKey(sf::Keyboard::Key key) {
        switch (key) {
            case sf::Keyboard::W:
            case sf::Keyboard::Up:
                return Key::UP;
            case sf::Keyboard::S:
            case sf::Keyboard::Down:
                return Key::DOWN;
            case sf::Keyboard::A:
            case sf::Keyboard::Left:
                return Key::LEFT;
            case sf::Keyboard::D:
            case sf::Keyboard::Right:
                return Key::RIGHT;
            case sf::Keyboard::Space:
            case sf::Keyboard::Enter:
                return Key::ACTION;
            case sf::Keyboard::R:
                return Key::RESTART;
            case sf::Keyboard::F11:
                return Key::FULLSCREEN;
            case sf::Keyboard::Escape:
                return Key::EXIT;
            default:
                return Key::UNDEFINED;
        }
    }
};

#endif //GAME_KEYBINDINGS_H