#include "RunScreen.h"
#include "WorldTVPowerCodes.h"

using namespace Applications::Infrared::TVBGone;

void RunScreen::stop()
{
    if (this->_isRunning)
        this->_stopping = true;

    while (this->_stopping || this->_isRunning)
    {
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void RunScreen::execute()
{
    this->_isRunning = true;
    this->_stopping = false;

    auto infrared = DeviceBase::getInstance()->getInterfaces().infrared;
    auto irSend = infrared->getIRSend();

    if (this->_region == TVBGoneRegion::AmericasAsia)
    {
        totalCodes = total_NAcodes;
        region = NA;
    }
    else
    {
        totalCodes = total_EUcodes;
        region = EU;
    }

    int lastProgress = 0;

    for (int i = 0; i < totalCodes; i++)
    {
        powerCode = this->_region == TVBGoneRegion::AmericasAsia
                        ? NApowerCodes[i]
                        : EUpowerCodes[i];

        const uint8_t freq = powerCode->timer_val;
        const uint8_t numpairs = powerCode->numpairs;
        const uint8_t bitcompression = powerCode->bitcompression;
        code_ptr = 0;

        for (uint8_t k = 0; k < numpairs; k++)
        {
            uint16_t ti;
            ti = (read_bits(bitcompression)) * 2;

            offtime = powerCode->times[ti];
            ontime = powerCode->times[ti + 1];

            rawData[k * 2] = offtime * 10;
            rawData[(k * 2) + 1] = ontime * 10;
        }

        irSend->sendRaw(rawData, (numpairs * 2), freq);

        bitsleft_r = 0;

        auto progress = int((float)i / totalCodes * 100);

        if (progress > lastProgress)
        {
            this->_progressBar.setProgress(progress);
            this->_progressBar.render(this->_tft);
            lastProgress = progress;
        }

        if (this->_stopping)
            break;

        vTaskDelay(pdMS_TO_TICKS(500));
    }

    this->_progressBar.setProgress(100);
    this->_progressBar.render(this->_tft);

    infrared->disable();

    this->_isRunning = false;
    this->_stopping = false;
}

void RunScreen::start()
{
    if (this->_isRunning)
        return;

    xTaskCreatePinnedToCore([](void *param)
                            {
                                auto screen = static_cast<RunScreen *>(param);
                                screen->execute();
                                vTaskDelete(nullptr); },
                            "TVBGoneApp_RunScreen", configMINIMAL_STACK_SIZE + 2048, this, 1, nullptr, portNUM_PROCESSORS - 1);
}

void RunScreen::render(std::shared_ptr<TFT_eSPI> tft)
{
    auto displaySettings = this->getDisplaySettings();

    this->setTextSizeSmall(tft);

    String title = this->_region == TVBGoneRegion::AmericasAsia
                       ? "Americas / Asia"
                       : "EU/MidEast/Africa";

    auto titleX = (displaySettings.width - tft->textWidth(title)) / 2;

    if (titleX < 0)
        titleX = 0;

    tft->drawString(title, titleX, this->_topBarHeight + 5);
    tft->setCursor(0, displaySettings.height - 35);
    tft->println(this->translate("PressAnyButtonToStop"));

    int progressBarMargin = 10;
    this->_progressBar.setPosition(progressBarMargin, (displaySettings.height - this->_progressBar.getHeight()) / 2);
    this->_progressBar.setWidth(displaySettings.width - (progressBarMargin * 2));
    this->_progressBar.render(tft);
}

void RunScreen::buttonSelectPressed()
{
    this->stop();
    Screen::buttonBackPressed();
}

void RunScreen::buttonNextPressed()
{
    this->stop();
    Screen::buttonBackPressed();
}

void RunScreen::buttonPreviousPressed()
{
    this->stop();
    Screen::buttonBackPressed();
}

void RunScreen::buttonBackPressed()
{
    this->stop();
    Screen::buttonBackPressed();
}
