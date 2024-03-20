#ifdef M5STICKCPLUS

#pragma once

#include <memory>

#define MIC_PIN_DATA 34
#define MIC_PIN_CLK 0

#include "../../domain/entities/MicrophoneInterfaceBase.h"
#include "../utility/Mic_Class.hpp"

#ifdef __cplusplus
extern "C"
{
#endif
    namespace Infrastructure::M5StickCPlus
    {
        class MicrophoneInterface : public Domain::Entities::MicrophoneInterfaceBase
        {
        private:
            size_t _rec_number = 200;
            size_t _rec_length = 240;
            size_t _rec_size() { return _rec_number * _rec_length; }
            size_t _sample_rate = 44100;
            size_t _rec_idx = 2;
            uint8_t *_rec_data;

            m5::Mic_Class _mic;

        public:
            void begin();
            void loop();
            void enable();
            void disable();
        };
    }
#ifdef __cplusplus
}
#endif
#endif