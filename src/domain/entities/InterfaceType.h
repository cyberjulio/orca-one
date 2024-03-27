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
            Battery,
            Wifi,
            Bluetooth,
            Led,
            PowerManagement,
            SdCard,
            Gps,
            Keyboard,
            Buttons,
            Infrared,
			I2C
        };
    }
#ifdef __cplusplus
}
#endif
