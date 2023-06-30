#pragma once
#include "Global.hpp"

class GameFrame {
   public:
    sf::Font arial;    // font�t�@�C���p
    sf::Font digital;  // font�t�@�C���p

    sf::Text tTitle;  // title ����
    sf::Text tTimer;  // timer ����
    sf::Text nTimer;  // timer ���l

    sf::Text tClear;  // Game Clear ����
    sf::Text tOver;   // Game Over ����

    sf::RectangleShape frame;         // �Q�[���G���A
    const int GAME_FRAME_SIZE = 486;  // �Q�[���G���A�̃T�C�Y

    GameFrame();
    void SetGameText(sf::Font &font, sf::Text &text, std::string str, int size, float x, float y, sf::Color clr);
    void SetGameFrame();
    void GameEnd(sf::RenderWindow &window, bool clear, bool over);
    void update(std::string timer);
    void draw(sf::RenderWindow &window);
};