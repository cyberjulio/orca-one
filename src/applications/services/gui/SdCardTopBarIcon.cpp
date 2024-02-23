#include "SdCardTopBarIcon.h"

using namespace Applications::Services::GUI;

void SdCardTopBarIcon::render(std::shared_ptr<TFT_eSPI> tft)
{
    tft->fillRoundRect(this->_x, this->_y + 5, this->_width, this->_height, 3, THEME_PRIMARY_COLOR);
    tft->fillTriangle(this->_x + 5, this->_y + 7, this->_x + 10, this->_y + 2, this->_x + 15, this->_y + 7, THEME_BACKGROUND_COLOR);

    tft->setTextColor(THEME_BACKGROUND_COLOR);
    tft->setTextSize(1);
    tft->setCursor(this->_x + 10, this->_y + 10);
    tft->print("SD");
}

void SdCardTopBarIcon::setPosition(int x, int y)
{
    this->_x = x;
    this->_y = y;
}
