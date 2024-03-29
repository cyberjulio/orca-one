#pragma once

#include "../../services/gui/ScreenManager.h"
#include "../../taskmanager/TaskManager.h"
#include "../../../domain/entities/I2CInterfaceBase.h"
#include "../../../domain/entities/DeviceBase.h"
#include "PN532.h"
#include "PN532_I2C.h"
#include <cstdint>
#include <string>

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
		std::shared_ptr<I2CInterfaceBase> _i2cInterface;
		PN532_I2C *_pn532i2c;
		PN532 *_nfc;
        bool _isRunning = false;
        bool _stopping = false;
        bool _isAgain = true;
        void execute();
        String hexToString(uint8_t *data, uint8_t numBytes);
        void showInfo(String msg, int posX, int posY, std::shared_ptr<TFT_eSPI> tft);

      public:
        ReadTagRun(std::shared_ptr<TFT_eSPI> tft) : Screen(tft)
        {
			this->_i2cInterface = DeviceBase::getInstance()->getInterfaces().i2cInterface;
			this->_pn532i2c = new PN532_I2C(this->_i2cInterface->_wire);
			this->_nfc = new PN532(*this->_pn532i2c);
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
