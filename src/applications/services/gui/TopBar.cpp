#include "TopBar.h"

#include "../../../domain/entities/DeviceBase.h"

using namespace Applications::Services::GUI;
using namespace Domain::Entities;

void TopBar::render(std::shared_ptr<TFT_eSPI> tft)
{
    // tft->fillRect(0, 0, 240, this->_topBarHeight - 2, THEME_PRIMARY_COLOR);

    auto device = DeviceBase::getInstance();
    auto deviceName = device->getSettings()->getDeviceName();
    auto displayInterface = device->getInterfaces().displayInterface;
    auto displaySettings = displayInterface->getSettings();

    // tft->setTextColor(THEME_PRIMARY_COLOR);
    // this->setTextSizeTiny(tft);
    // auto deviceNameX = (displaySettings.width - tft->textWidth(deviceName)) / 2;
    // tft->drawString(deviceName, deviceNameX, 8);

    // this->_sdcardIcon->setPosition(5, 1);
    // this->_sdcardIcon->render(tft);

    // this->_batteryIcon->setPosition(displaySettings.width - this->_batteryIcon->getWidth() - 5, 5);
    // this->_batteryIcon->render(tft);
}