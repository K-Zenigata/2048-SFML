#include "../include/Panel.hpp"

#include <cmath>

Panel::Panel() {

    // パネルの数値に使うfontを取り込む //
    if (!font.loadFromFile(gh::ARIAL)) {
        throw("Could Not Load Font!");
    }
    
    setSize(sf::Vector2f(SIZE, SIZE));
}

void Panel::SetGamePanel(float x, float y, int num) {
    //
    this->setPosition(x, y);
    this->setFillColor(getPanelColor(num));

    // 0 の時は、textは無し //
    if (!num) return;

    text.setFont(font);
    text.setCharacterSize(50);
    text.setStyle(sf::Text::Bold);
    text.setString(std::to_string(num));

    // 数値の色 //
    sf::Color nClr;
    num < 5 ? nClr = clrs::NUMBER_1 : nClr = clrs::NUMBER_2;
    text.setFillColor(nClr);

    SetCenterPos();
}

// 数値をpanelの中央に表示させる //
void Panel::SetCenterPos() {
    sf::FloatRect textBounds = text.getLocalBounds();
    sf::FloatRect panelBounds = this->getGlobalBounds();

    text.setOrigin(textBounds.width / 2, textBounds.height / 2);

    int x = panelBounds.width / 2 + panelBounds.left - textBounds.left;
    int y = panelBounds.height / 2 + panelBounds.top - textBounds.top;

    text.setPosition(x, y);
}

sf::Color Panel::getPanelColor(int num) {
    sf::Color clr[12] = {
        clrs::C_BASE_PANEL,  // 0
        clrs::BACK_G2,       // 2
        clrs::BACK_G4,       // 4
        clrs::BACK_G8,       // 8
        clrs::BACK_G16,      // 16
        clrs::BACK_G32,      // 32
        clrs::BACK_G64,      // 64
        clrs::BACK_G128,     // 128
        clrs::BACK_G256,     // 256
        clrs::BACK_G512,     // 512
        clrs::BACK_G1024,    // 1024
        clrs::BACK_G2048     // 2048

    };

    // num が2の何乗かを調べる //
    int getNum = num == 0 ? 0 : log2(num);

    return clr[getNum];
}

void Panel::draw(sf::RenderWindow &window) {
    //
    window.draw(*this);
    window.draw(text);
}