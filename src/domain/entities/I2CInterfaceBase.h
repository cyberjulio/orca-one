#pragma once

#include "IInterface.h"
#include "InterfaceType.h"
#include "Wire.h"

#ifdef __cplusplus
extern "C"
{
#endif
    namespace Domain::Entities
    {
    class I2CInterfaceBase : public IInterface
    {
      public:
        InterfaceType getType();
        virtual void begin() = 0;
        virtual void begin(int sda_pin, int scl_pin) = 0;
        virtual void loop() = 0;
        virtual void end() = 0;
        TwoWire i2c = TwoWire(0);
    };
    } // namespace Domain::Entities
#ifdef __cplusplus
}
#endif
