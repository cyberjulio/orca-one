#ifdef M5STICKCPLUS

#pragma once

#include <memory>

#if defined(M5STICKCPLUS1_1)
#include "utility/AXP192.h"
#elif defined(M5STICKCPLUS2)
#define POWER_HOLD_PIN 4
#include <esp_adc_cal.h>
#include <soc/adc_channel.h>
static std::int32_t getBatteryAdcRaw(uint8_t adc_ch, uint8_t adc_unit);
#endif

#include "../../domain/entities/PowerManagementInterfaceBase.h"

#ifdef __cplusplus
extern "C"
{
#endif
    namespace Infrastructure::M5StickCPlus
    {
        class PowerManagementInterface : public Domain::Entities::PowerManagementInterfaceBase
        {
        public:
            void begin();
            int readBatteryLevel();

        private:
#if defined(M5STICKCPLUS1_1)
            AXP192 _axp = AXP192();
#endif
        };
    }
#ifdef __cplusplus
}
#endif
#endif