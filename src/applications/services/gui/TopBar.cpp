#include "TopBar.h"

#include "../../../domain/entities/DeviceBase.h"

using namespace Applications::Services::GUI;
using namespace Domain::Entities;

void TopBar::render(std::shared_ptr<TFT_eSPI> tft)
{
    auto device = DeviceBase::getInstance();
    auto deviceName = device->getSettings()->getDeviceName();
    auto sdCard = device->getInterfaces().sdCard;
    auto displaySettings = this->getDisplaySettings();

    tft->setTextColor(THEME_PRIMARY_COLOR);

    if (sdCard->isActive())
    {
        this->_sdcardIcon->setPosition(displaySettings.width - this->_batteryIcon->getWidth() - 5 - 35, 1);
        this->_sdcardIcon->render(tft);
    }

    this->_batteryIcon->setPosition(displaySettings.width - this->_batteryIcon->getWidth() - 5, 5);
    this->_batteryIcon->render(tft);
}