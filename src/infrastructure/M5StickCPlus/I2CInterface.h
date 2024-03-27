#ifdef M5STICKCPLUS

#pragma once

#include <memory>

#include "../../domain/entities/I2CInterfaceBase.h"

#define SDA_PIN 32
#define SCL_PIN 33

#ifdef __cplusplus
extern "C"
{
#endif
    namespace Infrastructure::M5StickCPlus
    {
    class I2CInterface : public Domain::Entities::I2CInterfaceBase
    {
      public:
        I2CInterface();
        void begin();
        void begin(int sda_pin, int scl_pin);
        void loop();
        void end();
    };
    } // namespace Infrastructure::M5StickCPlus
#ifdef __cplusplus
}
#endif
#endif
