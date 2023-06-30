#pragma once
#include <SFML/Graphics.hpp>

class KeyHandler {
   public:
    bool left = false;
    bool right = false;
    bool up = false;
    bool down = false;

    void KeyDownHandler(sf::Event e) {
        if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Right) {
            right = true;
        }

        if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Left) {
            left = true;
        }

        if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Up) {
            up = true;
        }

        if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Down) {
            down = true;
        }
    };

    void KeyUpHandler(sf::Event e) {
        if (e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::Right) {
            right = false;
        }

        if (e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::Left) {
            left = false;
        }

        if (e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::Up) {
            up = false;
        }

        if (e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::Down) {
            down = false;
        }
    };
};