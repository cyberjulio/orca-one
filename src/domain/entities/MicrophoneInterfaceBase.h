#pragma once

#include "IInterface.h"
#include "InterfaceType.h"
#include "EventHandler.h"
#include "RecordedSample.h"

#ifdef __cplusplus
extern "C"
{
#endif
    namespace Domain::Entities
    {
        class MicrophoneInterfaceBase : public IInterface
        {
        public:
            MicrophoneInterfaceBase()
            {
                this->_active = false;
            }

            InterfaceType getType();
            virtual void begin() = 0;
            virtual void loop() = 0;
            void registerOnRecorded(std::function<void(RecordedSample)> handler);

        protected:
            GenericEventHandler<RecordedSample> _onRecorded;
        };
    }
#ifdef __cplusplus
}
#endif
