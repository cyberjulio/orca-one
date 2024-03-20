#ifdef M5STICKCPLUS

#include "MicrophoneInterface.h"
#include "../../domain/entities/RecordedSample.h"

using namespace Infrastructure::M5StickCPlus;

void MicrophoneInterface::begin()
{
    auto cfg = this->_mic.config();

    cfg.pin_data_in = MIC_PIN_DATA;
    cfg.pin_ws = MIC_PIN_CLK;

    this->_mic.config(cfg);
}

void MicrophoneInterface::loop()
{
    if (this->_active && this->_mic.isEnabled())
    {
        auto data = &this->_rec_data[this->_rec_idx * this->_rec_length];

        if (this->_mic.record(data, this->_rec_length, this->_sample_rate))
        {
            Domain::Entities::RecordedSample sample;

            sample.sample_rate = this->_sample_rate;

            if (++this->_rec_idx >= this->_rec_number)
            {
                int start_pos = this->_rec_idx * this->_rec_length;

                if (start_pos < this->_rec_size())
                {
                    sample.raw_data = &this->_rec_data[start_pos];
                    sample.array_len = this->_rec_size() - start_pos;
                }
                else if (start_pos > 0)
                {
                    sample.raw_data = this->_rec_data;
                    sample.array_len = start_pos;
                }

                this->_onRecorded.fireEvent(sample);

                this->_rec_idx = 0;
            }
        }
    }
}

void MicrophoneInterface::enable()
{
    this->_rec_data = (typeof(this->_rec_data))heap_caps_malloc(this->_rec_size() * sizeof(uint8_t), MALLOC_CAP_8BIT);
    memset(this->_rec_data, 0, this->_rec_size() * sizeof(uint8_t));

    MicrophoneInterfaceBase::enable();
}

void MicrophoneInterface::disable()
{
    if (!this->_active)
        return;

    MicrophoneInterfaceBase::disable();

    while (this->_mic.isRecording())
        vTaskDelay(pdMS_TO_TICKS(500));

    if (this->_rec_data != nullptr)
    {
        heap_caps_free(this->_rec_data);
        this->_rec_data = nullptr;
    }
}

#endif
