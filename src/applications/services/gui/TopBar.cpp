#include "TopBar.h"

#include "../../../domain/entities/DeviceBase.h"

using namespace Applications::Services::GUI;
using namespace Domain::Entities;

void TopBar::render(std::shared_ptr<TFT_eSPI> tft)
{
    auto device = DeviceBase::getInstance();
    auto deviceName = device->getSettings()->getDeviceName();
    auto displayInterface = device->getInterfaces().displayInterface;
    auto sdCardInterface = device->getInterfaces().sdCardInterface;
    auto displaySettings = displayInterface->getSettings();

    tft->setTextColor(THEME_PRIMARY_COLOR);

    if (sdCardInterface->isActive())
    {
        this->_sdcardIcon->setPosition(displaySettings.width - this->_batteryIcon->getWidth() - 5 - 35, 1);
        this->_sdcardIcon->render(tft);
    }

    this->_batteryIcon->setPosition(displaySettings.width - this->_batteryIcon->getWidth() - 5, 5);
    this->_batteryIcon->render(tft);
}