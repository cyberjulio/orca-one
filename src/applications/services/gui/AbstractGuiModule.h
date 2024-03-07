#pragma once

#include <memory>
#include <WString.h>
#include <TFT_eSPI.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "../../../Consts.h"
#include "../../../domain/entities/DisplayInterfaceBase.h"
#include "../../../domain/entities/DisplaySettings.h"

#ifdef __cplusplus
extern "C"
{
#endif
    namespace Applications::Services::GUI
    {
        class AbstractGuiModule
        {
        protected:
            const int _topBarHeight = 25;
            String _id;
            std::shared_ptr<Domain::Entities::DisplayInterfaceBase> getDisplayInterface();
            Domain::Entities::DisplaySettings getDisplaySettings();
            String translate(String key);

        public:
            virtual void render(std::shared_ptr<TFT_eSPI> tft) = 0;
            virtual void setId(String id);
            virtual const String getId();
            virtual void setTextSizeBig(std::shared_ptr<TFT_eSPI> tft);
            virtual void setTextSizeMedium(std::shared_ptr<TFT_eSPI> tft);
            virtual void setTextSizeSmall(std::shared_ptr<TFT_eSPI> tft);
            virtual void setTextSizeTiny(std::shared_ptr<TFT_eSPI> tft);
            virtual void drawBorderedText(std::shared_ptr<TFT_eSPI> tft, String text, int x, int y, int borderSize, uint16_t textColor, uint16_t borderColor);
        };
    }
#ifdef __cplusplus
}
#endif