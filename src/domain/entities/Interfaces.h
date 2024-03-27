#pragma once

#include <memory>

#include "DisplayInterfaceBase.h"
#include "PowerManagementInterfaceBase.h"
#include "BatteryInterfaceBase.h"
#include "WifiInterfaceBase.h"
#include "BluetoothInterfaceBase.h"
#include "LedInterfaceBase.h"
#include "SdCardInterfaceBase.h"
#include "GpsInterfaceBase.h"
#include "KeyboardInterfaceBase.h"
#include "ButtonsInterfaceBase.h"
#include "InfraredInterfaceBase.h"
#include "I2CInterfaceBase.h"

namespace Domain::Entities
{
    struct Interfaces
    {
        std::shared_ptr<DisplayInterfaceBase> displayInterface;
        std::shared_ptr<ButtonsInterfaceBase> buttonsInterface;
        std::shared_ptr<PowerManagementInterfaceBase> powerManagementInterface;
        std::shared_ptr<KeyboardInterfaceBase> keyboardInterface;
        std::shared_ptr<InfraredInterfaceBase> infraredInterface;
        std::shared_ptr<LedInterfaceBase> ledInterface;
		std::shared_ptr<I2CInterfaceBase> i2cInterface;
        std::shared_ptr<BatteryInterfaceBase> batteryInterface;
        std::shared_ptr<WifiInterfaceBase> wifiInterface;
        std::shared_ptr<BluetoothInterfaceBase> bluetoothInterface;
        std::shared_ptr<SdCardInterfaceBase> sdCardInterface;
        std::shared_ptr<GpsInterfaceBase> gpsInterface;
    };
}
