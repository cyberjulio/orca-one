#ifdef M5CARDPUTER

#include "Device.h"
#include "DisplayInterface.h"
#include "KeyboardInterface.h"
#include "ButtonsInterface.h"
#include "InfraredInterface.h"
#include "PowerManagementInterface.h"

using namespace Infrastructure::M5Cardputer;

Device::Device() : DeviceBase({std::make_shared<DisplayInterface>(),
                               std::make_shared<ButtonsInterface>(),
                               std::make_shared<PowerManagementInterface>(),
                               std::make_shared<KeyboardInterface>(),
                               std::make_shared<InfraredInterface>()})
{
}

String Device::getName()
{
    return "M5Cardputer";
}

void Infrastructure::M5Cardputer::Device::begin()
{
    Domain::Entities::DeviceBase::begin();
}

void Infrastructure::M5Cardputer::Device::loop()
{
    Domain::Entities::DeviceBase::loop();
}

#endif
