#include "BatteryTopBarIcon.h"

#include "../../../domain/entities/DeviceBase.h"

using namespace Applications::Services::GUI;
using namespace Domain::Entities;

void BatteryTopBarIcon::render(std::shared_ptr<TFT_eSPI> tft)
{
    auto powerManagementInterface = DeviceBase::getInstance()->getInterfaces().powerManagementInterface;

    auto chargeLevel = powerManagementInterface->getLastBatteryLevel();;
    int chargeWidth = map(chargeLevel, 0, 100, 0, this->_width);

    tft->drawRoundRect(this->_x, this->_y, this->_width, this->_height, 3, THEME_PRIMARY_COLOR);
    tft->fillRoundRect(this->_x, this->_y, chargeWidth, this->_height, 3, THEME_PRIMARY_COLOR);

    this->setTextSizeTiny(tft);
    auto textChargeLevel = String(chargeLevel);
    this->drawBorderedText(tft, textChargeLevel, this->_x + (this->_width - tft->textWidth(textChargeLevel)) / 2, this->_y + 5, 1, THEME_BACKGROUND_COLOR, THEME_PRIMARY_COLOR);
}

void BatteryTopBarIcon::setPosition(int x, int y)
{
    this->_x = x;
    this->_y = y;
}

int BatteryTopBarIcon::getWidth()
{
    return this->_width;
}
