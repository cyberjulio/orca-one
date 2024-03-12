#pragma once

#ifdef __cplusplus
extern "C"
{
#endif
    namespace Domain::Entities
    {
        enum InterfaceType
        {
            Display,
            Wifi,
            Bluetooth,
            Led,
            PowerManagement,
            SdCard,
            Gps,
            Keyboard,
            Buttons,
            Infrared,
			I2C,
            Microphone
        };
    }
#ifdef __cplusplus
}
#endif
