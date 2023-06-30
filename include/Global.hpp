#pragma once
#include <SFML/Graphics.hpp>
#include <iomanip>
#include <iostream>
#include <string>

namespace gh {
const int WINDOW_W = 550;
const int WINDOW_H = 650;
const int PANEL_SIZE = 113;
const int OFFSET_X = 40;
const int OFFSET_Y = 150;
const int MARGIN = 7;
const int COLS = 4;
const int ROWS = 4;

const std::string ARIAL = "../assets/arial.ttf";
const std::string DIGITAL = "../assets/digital-7.ttf";

}  // namespace gh

namespace clrs {

const sf::Color C_TITLE = sf::Color(255, 127, 80);  // rgb(255, 127, 80)

const sf::Color C_SCORE_STR = sf::Color(233, 150, 122);  // rgb(233, 150, 122)

const sf::Color C_SCORE_NUM = sf::Color(255, 235, 205);  // rgb(255, 235, 205)

const sf::Color C_SCORE_AREA = sf::Color(255, 235, 195);  // rgb(255, 235, 195)

// base stage color
const sf::Color C_STAGE = sf::Color(187, 173, 160);  // rgb(187, 173, 160)

// base panel color
const sf::Color C_BASE_PANEL = sf::Color(205, 193, 180);  // rgb(205, 193, 180)

// 2, 4 number color
const sf::Color NUMBER_1 = sf::Color(119, 110, 101);  // rgb(119, 110, 101)

// 8, 16, 32, 64, 128, 256, 512, 1024, 2048 number color
const sf::Color NUMBER_2 = sf::Color(249, 246, 242);  // rgb(249, 246, 242)

// 2 background color
const sf::Color BACK_G2 = sf::Color(238, 228, 218);  // rgb(238, 228, 218)

// 4 background color
const sf::Color BACK_G4 = sf::Color(237, 224, 200);  // rgb(237, 224, 200)

// 8 background color
const sf::Color BACK_G8 = sf::Color(242, 177, 121);  // rgb(242, 177, 121)

// 16 background color
const sf::Color BACK_G16 = sf::Color(245, 149, 99);  // rgb(245, 149, 99)

// 32 background color
const sf::Color BACK_G32 = sf::Color(246, 124, 95);  // rgb(246, 124, 95)

// 64 background color
const sf::Color BACK_G64 = sf::Color(246, 94, 59);  // rgb(246, 94, 59)

// 128 background color
const sf::Color BACK_G128 = sf::Color(237, 207, 114);  // rgb(237, 207, 114)

// 256 background color
const sf::Color BACK_G256 = sf::Color(237, 204, 97);  // rgb(237, 204, 97)

// 512 background color
const sf::Color BACK_G512 = sf::Color(237, 200, 80);  // rgb(237, 200, 80)

// 1024 background color
const sf::Color BACK_G1024 = sf::Color(237, 197, 63);  // rgb(237, 197, 63)

// 2048 background color
const sf::Color BACK_G2048 = sf::Color(237, 194, 46);  // rgb(237, 194, 46)

// Game Clear color
const sf::Color GameClear = sf::Color(65, 139, 59);  // rgb(65, 139, 59)

// Game Over color
const sf::Color GameOver = sf::Color(130, 11, 11);  // rgb(130, 11, 11)

}  // namespace clrs