#include "SdCardTopBarIcon.h"

using namespace Applications::Services::GUI;

void SdCardTopBarIcon::render(std::shared_ptr<TFT_eSPI> tft)
{
    auto primaryColor = this->getPrimaryColor();
    auto backgroundColor = this->getBackgroundColor();

    tft->fillRoundRect(this->_x, this->_y + 5, this->_width, this->_height, 3, primaryColor);
    tft->fillTriangle(this->_x + 5, this->_y + 7, this->_x + 10, this->_y + 2, this->_x + 15, this->_y + 7, backgroundColor);

    tft->setTextColor(backgroundColor);
    tft->setTextSize(1);
    tft->setCursor(this->_x + 10, this->_y + 10);
    tft->print("SD");
}

void SdCardTopBarIcon::setPosition(int x, int y)
{
    this->_x = x;
    this->_y = y;
}
