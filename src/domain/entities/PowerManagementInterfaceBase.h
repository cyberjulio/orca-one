#pragma once

#include "IInterface.h"
#include "InterfaceType.h"
#include "EventHandler.h"

#ifdef __cplusplus
extern "C"
{
#endif
    namespace Domain::Entities
    {
        class PowerManagementInterfaceBase : public IInterface
        {
        public:
            InterfaceType getType();

            virtual void begin();
            virtual void loop();
            void registerBatteryLevelChanged(std::function<void()> handler);
            int getLastBatteryLevel();
            virtual int readBatteryLevel() = 0;

        protected:
            EventHandler _onBatteryLevelChanged = EventHandler();
            int _lastBatteryLevel = -1;
        };
    }
#ifdef __cplusplus
}
#endif