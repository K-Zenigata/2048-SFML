#pragma once
#include "Global.hpp"

class Panel : public sf::RectangleShape {
   public:
    const int SIZE = gh::PANEL_SIZE;
    sf::Font font;
    sf::Text text;

    Panel();
    void SetGamePanel(float x, float y, int num);
    void SetCenterPos();
    sf::Color getPanelColor(int num);
    void draw(sf::RenderWindow &window);
};