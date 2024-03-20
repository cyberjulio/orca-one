#include "PowerManagementInterfaceBase.h"

using namespace Domain::Entities;

InterfaceType PowerManagementInterfaceBase::getType()
{
    return InterfaceType::PowerManagement;
}

void PowerManagementInterfaceBase::loop()
{
    auto batteryLevel = this->readBatteryLevel();

    if (batteryLevel != this->_lastBatteryLevel)
    {
        this->_lastBatteryLevel = batteryLevel;
        this->_onBatteryLevelChanged.fireEvent(batteryLevel);
    }
}

void PowerManagementInterfaceBase::begin()
{
    auto batteryLevel = this->readBatteryLevel();

    if (batteryLevel != this->_lastBatteryLevel)
    {
        this->_lastBatteryLevel = batteryLevel;
        this->_onBatteryLevelChanged.fireEvent(batteryLevel);
    }
}

void PowerManagementInterfaceBase::registerBatteryLevelChanged(std::function<void(int)> handler)
{
    this->_onBatteryLevelChanged.addHandler(handler);
}

int PowerManagementInterfaceBase::getLastBatteryLevel()
{
    return this->_lastBatteryLevel;
}
