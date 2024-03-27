#ifdef M5STICKCPLUS

#include "Device.h"
#include "DisplayInterface.h"
#include "ButtonsInterface.h"
#include "PowerManagementInterface.h"
#include "LedInterface.h"
#include "InfraredInterface.h"
#include "I2CInterface.h"

using namespace Infrastructure::M5StickCPlus;

Device::Device() : DeviceBase({std::make_shared<DisplayInterface>(),
                               std::make_shared<ButtonsInterface>(),
                               std::make_shared<PowerManagementInterface>(),
                               nullptr,
                               std::make_shared<InfraredInterface>(),
                               std::make_shared<LedInterface>(), 
							   std::make_shared<I2CInterface>()})
{
}

String Device::getName()
{
#if defined(M5STICKCPLUS1_1)
    return "M5StickC PLUS 1.1";
#elif defined(M5STICKCPLUS2)
    return "M5StickC PLUS2";
#endif
}

void Infrastructure::M5StickCPlus::Device::begin()
{
    Domain::Entities::DeviceBase::begin();
}

void Infrastructure::M5StickCPlus::Device::loop()
{
    Domain::Entities::DeviceBase::loop();
}

#endif
