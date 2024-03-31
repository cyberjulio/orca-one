#pragma once

#include <WString.h>
#include <TFT_eSPI.h>

#include "AbstractGuiModule.h"
#include "../../AppContext.h"

using namespace Domain::Entities;

#ifdef __cplusplus
extern "C"
{
#endif
    namespace Applications::Services::GUI
    {
        class ProgressBar : public AbstractGuiModule
        {
        protected:
            int _borderColor = -1;
            int _backgroundColor = -1;
            int _progressColor = -1;
            int _textColor = -1;
            int _width = -1;
            int _height = 25;
            int _x = -1;
            int _y = -1;
            int _progress = 0;
            std::function<void()> _onClick = nullptr;

        public:
            ProgressBar();

            void render(std::shared_ptr<TFT_eSPI> tft);

            void setBorderColor(int color);
            void setBackgroundColor(int color);
            void setProgressColor(int color);
            void setTextColor(int color);
            void setWidth(int width);
            void setPosition(int x, int y);
            void setProgress(int progress);
            int getHeight();
        };
    }

#ifdef __cplusplus
}
#endif