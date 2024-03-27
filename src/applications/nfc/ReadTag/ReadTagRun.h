#pragma once

#include "../../services/gui/ScreenManager.h"
#include "../../taskmanager/TaskManager.h"
#include <cstdint>

using namespace Applications;
using namespace Applications::Services::GUI;

#ifdef __cplusplus
extern "C"
{
#endif
    namespace Applications::Nfc::ReadTag
    {
    class ReadTagRun : public Screen
    {
      private:
        bool _isRunning = false;
        bool _stopping = false;
        bool _isAgain = true;
        void execute();
        String hexToString(uint8_t *data, uint8_t numBytes);
        void showInfo(String msg, int posX, int posY, std::shared_ptr<TFT_eSPI> tft);

      public:
        ReadTagRun(std::shared_ptr<TFT_eSPI> tft) : Screen(tft)
        {
        }

        void render(std::shared_ptr<TFT_eSPI> tft);
        void buttonSelectPressed();
        void buttonNextPressed();
        void buttonPreviousPressed();
        void buttonBackPressed();

        void stop();
        void start();
    };
    } // namespace Applications::Nfc::ReadTag
#ifdef __cplusplus
}
#endif
