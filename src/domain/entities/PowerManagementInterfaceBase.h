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
            void registerBatteryLevelChanged(std::function<void(int)> handler);
            int getLastBatteryLevel();
            virtual int readBatteryLevel() = 0;

        protected:
            GenericEventHandler<int> _onBatteryLevelChanged;
            int _lastBatteryLevel = -1;
        };
    }
#ifdef __cplusplus
}
#endif