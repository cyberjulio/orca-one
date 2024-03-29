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
        virtual void begin();
        virtual void begin(int sda_pin, int scl_pin);
        virtual void loop();
        virtual void end();
        TwoWire *_wire = nullptr;
    };
    } // namespace Domain::Entities
#ifdef __cplusplus
}
#endif
