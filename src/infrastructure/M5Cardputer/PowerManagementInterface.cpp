#ifdef M5CARDPUTER

#include "PowerManagementInterface.h"

#include <driver/adc.h>
#include <esp_adc_cal.h>

using namespace Infrastructure::M5Cardputer;

#define ADC1_CHAN0 ADC1_CHANNEL_9
#define ADC2_CHAN0 ADC2_CHANNEL_0
static const char *TAG_CH[2][10] = {{"ADC1_CH2"}, {"ADC2_CH0"}};
#define ADC_ATTEN ADC_ATTEN_DB_11
#define ADC_CALI_SCHEME ESP_ADC_CAL_VAL_EFUSE_TP_FIT
static esp_adc_cal_characteristics_t adc1_chars;
#undef ADC_WIDTH_BIT_DEFAULT
#define ADC_WIDTH_BIT_DEFAULT (adc_bits_width_t)((int)ADC_WIDTH_MAX - 1)
static int adc_raw[2][10];

static bool adc_calibration_init(void)
{
    esp_err_t ret;
    bool cali_enable = false;

    ret = esp_adc_cal_check_efuse(ADC_CALI_SCHEME);
    
    if (ret == ESP_OK)
    {
        cali_enable = true;
        esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN, ADC_WIDTH_BIT_DEFAULT, 0, &adc1_chars);
    }

    return cali_enable;
}

void PowerManagementInterface::begin()
{
    this->_calibrationEnabled = adc_calibration_init();

    adc1_config_width(ADC_WIDTH_BIT_DEFAULT);
    adc1_config_channel_atten(ADC1_CHAN0, ADC_ATTEN);

    PowerManagementInterfaceBase::begin();
}

int PowerManagementInterface::readBatteryLevel()
{
    adc_raw[0][0] = adc1_get_raw(ADC1_CHAN0);

    if (this->_calibrationEnabled)
    {
        auto bat_v = esp_adc_cal_raw_to_voltage(adc_raw[0][0], &adc1_chars);

        if (bat_v >= 4.12)
            return 100;
        else if (bat_v >= 3.88)
            return 75;
        else if (bat_v >= 3.61)
            return 50;
        else if (bat_v >= 3.40)
            return 25;
        else
            return 0;
    }

    return -1;
}

#endif