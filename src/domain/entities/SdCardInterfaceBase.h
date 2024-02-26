#pragma once

#include <SPI.h>
#include <SD.h>

#include "IInterface.h"
#include "InterfaceType.h"

#ifdef __cplusplus
extern "C"
{
#endif
    namespace Domain::Entities
    {
        class SdCardInterfaceBase : public IInterface
        {
        private:
            SPIClass *_spi = nullptr;
            bool _initialized = false;

        public:
            SdCardInterfaceBase();

            InterfaceType getType();
            virtual void begin();
            virtual void loop();
            virtual bool isActive();
        };
    }
#ifdef __cplusplus
}
#endif
