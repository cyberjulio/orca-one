#include "ReadTagRunScreen.h"

using namespace Applications::Nfc::ReadTag;


void ReadTagRun::stop()
{
    if (this->_isRunning)
        this->_stopping = true;

    while (this->_stopping || this->_isRunning)
    {
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void ReadTagRun::execute()
{
    this->_isRunning = true;
    this->_stopping = false;

    uint8_t success;
    uint8_t uid[] = {0, 0, 0, 0, 0, 0, 0};
    uint8_t uidLength;
    uint8_t *nfcBuffer;
    uint8_t nfcBufferLength;

    uint32_t versiondata = this->_nfc->getFirmwareVersion();
    if (!versiondata)
    {
        this->_tft->fillScreen(_backgroundColor);
        this->showInfo(TRANSLATE("PN532NotFound"), 15, 35, this->_tft);
        vTaskDelay(pdMS_TO_TICKS(3000));
        // this->buttonBackPressed();
        this->_i2cInterface->end();
        this->_isRunning = false;
        this->_stopping = false;
        ScreenManager::setCurrentScreen(this->_previousScreen);
    }

    while (true)
    {
        if (this->_isAgain)
        {
            this->_tft->fillScreen(_backgroundColor);
            this->showInfo(TRANSLATE("WaitTag"), 10, 35, this->_tft);

            success = this->_nfc->readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

            if (success)
            {
                nfcBuffer = this->_nfc->getBuffer(&nfcBufferLength);
                this->_tft->fillScreen(_backgroundColor);
                this->showInfo("UID:" + this->hexToString(uid, uidLength), 15, 35, this->_tft);
                this->showInfo("ATQ:" + String(nfcBuffer[3], HEX), 15, this->_tft->getCursorY() + 5, this->_tft);
                this->showInfo("SAK:" + String(nfcBuffer[4], HEX), 15, this->_tft->getCursorY() + 5, this->_tft);
            }
            else
            {
                this->_tft->fillScreen(_backgroundColor);
                this->showInfo(TRANSLATE("ErrorTimeOut"), 40, 35, this->_tft);
            }
            this->_isAgain = false;
        }

        if (this->_stopping)
            break;

        vTaskDelay(pdMS_TO_TICKS(500));
    }

    this->_i2cInterface->end();
	delete this->_pn532i2c;
	delete this->_nfc;

    this->_isRunning = false;
    this->_stopping = false;
}

void ReadTagRun::start()
{
    if (this->_isRunning)
        return;

    this->_nfc->begin();
    this->_nfc->SAMConfig();

    xTaskCreatePinnedToCore(
        [](void *param) {
            auto screen = static_cast<ReadTagRun *>(param);
            screen->execute();
            vTaskDelete(nullptr);
        },
        "ReadTag_Run", configMINIMAL_STACK_SIZE + 2048, this, 1, nullptr, portNUM_PROCESSORS - 1);
}

void ReadTagRun::render(std::shared_ptr<TFT_eSPI> tft)
{

    this->setTextSizeSmall(tft);
    tft->setTextColor(_primaryColor);

    String title = TRANSLATE("ReadMifare");
    auto titleX = (_displaySettings.width - tft->textWidth(title)) / 2;

    if (titleX < 0)
        titleX = 0;

    tft->drawString(title, titleX, 5);
    String bottomText = String("OK:") + TRANSLATE("Again") + " ESC:" + TRANSLATE("Exit");
    tft->setCursor((_displaySettings.width - tft->textWidth(bottomText)) / 2, _displaySettings.height - 20);
    tft->print(bottomText);
}

void ReadTagRun::showInfo(String msg, int posX, int posY, std::shared_ptr<TFT_eSPI> tft)
{
    this->render(this->_tft);
    tft->setCursor(posX, posY);
    tft->println(msg);
}

String ReadTagRun::hexToString(uint8_t *data, uint8_t numBytes)
{
    String result = "";

    for (uint8_t i = 0; i < numBytes; i++)
    {
        if (data[i] < 0x10)
        {
            result += " 0";
        }
        else
        {
            result += " ";
        }
        result += String(data[i], HEX);
    }

    return result;
}

void ReadTagRun::buttonSelectPressed()
{
    this->_isAgain = true;
}

void ReadTagRun::buttonNextPressed()
{
    this->stop();
    Screen::buttonBackPressed();
}

void ReadTagRun::buttonPreviousPressed()
{
    this->stop();
    Screen::buttonBackPressed();
}

void ReadTagRun::buttonBackPressed()
{
    this->stop();
    Screen::buttonBackPressed();
}
