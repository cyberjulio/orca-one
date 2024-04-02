#pragma once

#include <WString.h>
#include <TFT_eSPI.h>

#include "AbstractGuiModule.h"

#ifdef __cplusplus
extern "C"
{
#endif
    namespace Applications::Services::GUI
    {
        class BatteryTopBarIcon : public AbstractGuiModule
        {
        private:
            int _x = 0;
            int _y = 0;
            int _width = 30;
            int _height = 16;

        public:
            void render(std::shared_ptr<TFT_eSPI> tft);
            void setPosition(int x, int y);
            int getWidth();
        };
    }

#ifdef __cplusplus
}
#endif