#ifdef M5CARDPUTER

#pragma once

#include <memory>

#include "../../domain/entities/PowerManagementInterfaceBase.h"

#define VBAT_PIN 10

#ifdef __cplusplus
extern "C"
{
#endif
    namespace Infrastructure::M5Cardputer
    {
        class PowerManagementInterface : public Domain::Entities::PowerManagementInterfaceBase
        {
        private:
            bool _calibrationEnabled = false;

        public:
            void begin();
            int readBatteryLevel();
        };
    }
#ifdef __cplusplus
}
#endif
#endif