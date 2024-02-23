#pragma once

#include <WString.h>
#include <TFT_eSPI.h>

#include "AbstractGuiModule.h"
#include "BatteryTopBarIcon.h"
#include "SdCardTopBarIcon.h"

#ifdef __cplusplus
extern "C"
{
#endif
    namespace Applications::Services::GUI
    {
        class TopBar : public AbstractGuiModule
        {
        private:
            BatteryTopBarIcon *_batteryIcon = new BatteryTopBarIcon();
            SdCardTopBarIcon *_sdcardIcon = new SdCardTopBarIcon();

        public:
            void render(std::shared_ptr<TFT_eSPI> tft);
        };
    }

#ifdef __cplusplus
}
#endif