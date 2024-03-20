#pragma once

#include <memory>

#include "DisplayInterfaceBase.h"
#include "PowerManagementInterfaceBase.h"
#include "WifiInterfaceBase.h"
#include "BluetoothInterfaceBase.h"
#include "LedInterfaceBase.h"
#include "SdCardInterfaceBase.h"
#include "GpsInterfaceBase.h"
#include "KeyboardInterfaceBase.h"
#include "ButtonsInterfaceBase.h"
#include "InfraredInterfaceBase.h"
#include "I2CInterfaceBase.h"
#include "MicrophoneInterfaceBase.h"

namespace Domain::Entities
{
    struct Interfaces
    {
        std::shared_ptr<DisplayInterfaceBase> display;
        std::shared_ptr<ButtonsInterfaceBase> buttons;
        std::shared_ptr<PowerManagementInterfaceBase> powerManagement;
        std::shared_ptr<KeyboardInterfaceBase> keyboard;
        std::shared_ptr<InfraredInterfaceBase> infrared;
        std::shared_ptr<LedInterfaceBase> led;
		std::shared_ptr<I2CInterfaceBase> i2c;
        std::shared_ptr<MicrophoneInterfaceBase> microphone;
        std::shared_ptr<WifiInterfaceBase> wifi;
        std::shared_ptr<BluetoothInterfaceBase> bluetooth;
        std::shared_ptr<SdCardInterfaceBase> sdCard;
        std::shared_ptr<GpsInterfaceBase> gps;
    };
}
