#ifdef M5STICKCPLUS

#include "PowerManagementInterface.h"

using namespace Infrastructure::M5StickCPlus;

void PowerManagementInterface::begin()
{
#if defined(M5STICKCPLUS1_1)
    this->_axp.begin();
#elif defined(M5STICKCPLUS2)
    pinMode(POWER_HOLD_PIN, OUTPUT);
    digitalWrite(POWER_HOLD_PIN, HIGH);
#endif

    PowerManagementInterfaceBase::begin();
}

int PowerManagementInterface::readBatteryLevel()
{
    int currentBatteryLevel = this->_lastBatteryLevel;

#if defined(M5STICKCPLUS1_1)
    auto vbat = this->_axp.GetBatVoltage();
    currentBatteryLevel = ((vbat - 3.0) / 1.2) * 100;
#elif defined(M5STICKCPLUS2)
    auto adc_ch = ADC1_GPIO38_CHANNEL;
    auto adc_unit = 1;
    auto adc_ratio = 2.0f;

    auto mv = getBatteryAdcRaw(ADC1_GPIO38_CHANNEL, adc_unit) * adc_ratio;
    currentBatteryLevel = (mv - 3300) * 100 / (float)(4150 - 3350);
#endif

    if (currentBatteryLevel < 0)
        currentBatteryLevel = 0;

    if (currentBatteryLevel > 100)
        currentBatteryLevel = 100;

    return currentBatteryLevel;
}

#if defined(M5STICKCPLUS2)
static std::int32_t getBatteryAdcRaw(uint8_t adc_ch, uint8_t adc_unit)
{
    static constexpr int BASE_VOLTAGE = 3600;
    static esp_adc_cal_characteristics_t *adc_chars = nullptr;

    if (adc_chars == nullptr)
    {
        if (adc_unit == 2)
        {
            adc2_config_channel_atten((adc2_channel_t)adc_ch, ADC_ATTEN_DB_11);
        }
        else
        {
            adc1_config_width(ADC_WIDTH_BIT_12);
            adc1_config_channel_atten((adc1_channel_t)adc_ch, ADC_ATTEN_DB_11);
        }
        adc_chars = (esp_adc_cal_characteristics_t *)calloc(1, sizeof(esp_adc_cal_characteristics_t));
        esp_adc_cal_characterize((adc_unit_t)adc_unit, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, BASE_VOLTAGE, adc_chars);
    }

    int raw;

    if (adc_unit == 2)
    {
        adc2_get_raw((adc2_channel_t)adc_ch, adc_bits_width_t::ADC_WIDTH_BIT_12, &raw);
    }
    else
    {
        raw = adc1_get_raw((adc1_channel_t)adc_ch);
    }

    return esp_adc_cal_raw_to_voltage(raw, adc_chars);
}
#endif

#endif