#pragma once

#include "IInterface.h"
#include "InterfaceType.h"

#ifdef __cplusplus
extern "C"
{
#endif
    namespace Domain::Entities
    {
        class MicrophoneInterfaceBase : public IInterface
        {
        protected:
            size_t _sample_rate = 44100;
            size_t _max_buffer = 512;

        public:
            InterfaceType getType();
            virtual void begin() = 0;
            virtual void loop() = 0;
        };
    }
#ifdef __cplusplus
}
#endif
