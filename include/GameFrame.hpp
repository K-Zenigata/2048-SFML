#pragma once
#include "Global.hpp"

class GameFrame {
   public:
    sf::Font arial;    // fontファイル用
    sf::Font digital;  // fontファイル用

    sf::Text tTitle;  // title 文字
    sf::Text tTimer;  // timer 文字
    sf::Text nTimer;  // timer 数値

    sf::Text tClear;  // Game Clear 文字
    sf::Text tOver;   // Game Over 文字

    sf::RectangleShape frame;         // ゲームエリア
    const int GAME_FRAME_SIZE = 486;  // ゲームエリアのサイズ

    GameFrame();
    void SetGameText(sf::Font &font, sf::Text &text, std::string str, int size, float x, float y, sf::Color clr);
    void SetGameFrame();
    void GameEnd(sf::RenderWindow &window, bool clear, bool over);
    void update(std::string timer);
    void draw(sf::RenderWindow &window);
};