#include "../include/GameFrame.hpp"

GameFrame::GameFrame() {
    // fontÉtÉ@ÉCÉãÇÃì«Ç›çûÇ› //
    if (!arial.loadFromFile(gh::ARIAL)) {
        throw("Could Not Load Font!");
    }
    if (!digital.loadFromFile(gh::DIGITAL)) {
        throw("Could Not Load Font!");
    }
}

// window Ç… text Çï`âÊ //
void GameFrame::SetGameText(sf::Font &font, sf::Text &text, std::string str, int size, float x, float y, sf::Color clr) {
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(size);
    text.setPosition(x, y);
    text.setFillColor(clr);
}

// ÉQÅ[ÉÄÇÃògÇìhÇËÇ¬Ç‘ÇµÇ≈ï`âÊ //
void GameFrame::SetGameFrame() {
    frame.setSize(sf::Vector2f(GAME_FRAME_SIZE, GAME_FRAME_SIZE));
    frame.setPosition(gh::OFFSET_X - gh::MARGIN, gh::OFFSET_Y - gh::MARGIN);
    frame.setFillColor(clrs::C_SCORE_AREA);
}

// ÉQÅ[ÉÄÇ™èIóπÇµÇΩéûÇÃï`âÊ //
void GameFrame::GameEnd(sf::RenderWindow &window, bool clear, bool over) {

    if (clear) {
        // (font, text, str, size, x, y, clr)
        SetGameText(arial, tClear, "Game Clear", 90, 33, 320, clrs::GameClear);
    } else if (over) {
        SetGameText(arial, tOver, "Game Over", 90, 40, 320, clrs::GameOver);
    }

    window.draw(tClear);
    window.draw(tOver);
}

void GameFrame::update(std::string timer) {

    // (font, text, str, size, x, y, clr)
    // title //
    SetGameText(arial, tTitle, "2048", 100, gh::OFFSET_X, 10, clrs::C_TITLE);
    // str timer //
    SetGameText(arial, tTimer, "Timer", 30, 400, 20, clrs::C_SCORE_STR);

    // number timer //
    SetGameText(digital, nTimer, timer, 40, 350, 70, clrs::NUMBER_2);

    SetGameFrame();
}

void GameFrame::draw(sf::RenderWindow &window) {
    window.draw(tTitle);
    window.draw(tTimer);
    window.draw(nTimer);
    window.draw(frame);

}