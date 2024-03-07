#include "SplashScreen.h"

#include "../../../utility/FileUtility.h"
#include "../../../domain/entities/DeviceBase.h"

using namespace Applications::Services::GUI;
using namespace Domain::Entities;
using namespace Utility;

SplashScreen::SplashScreen(std::shared_ptr<TFT_eSPI> tft) : Screen(tft)
{
}

void SplashScreen::render(std::shared_ptr<TFT_eSPI> tft)
{
    auto device = DeviceBase::getInstance();
    auto displaySettings = this->getDisplaySettings();
    auto primaryColor = device->getSettings()->getPrimaryColor();
    auto backgroundColor = device->getSettings()->getBackgroundColor();
    auto splashFile = String("/imgs/splash_") + String(displaySettings.width) + String("x") + String(displaySettings.height) + String(".jpg");

    FileUtility::drawJpeg(SPIFFS, tft, splashFile.c_str(), 0, 0, displaySettings.width, displaySettings.height);

    vTaskDelay(pdMS_TO_TICKS(1000 * 2));

    tft->fillScreen(colorToUInt16(backgroundColor));
    tft->setTextColor(colorToUInt16(primaryColor));

    this->setTextSizeMedium(tft);
    auto title = String("Orca One");
    auto titleX = (displaySettings.width - tft->textWidth(title)) / 2;
    tft->drawString(title, titleX, 5);

    this->setTextSizeSmall(tft);
    auto version = String(BUILD_NUMBER);
    auto versionX = (displaySettings.width - tft->textWidth(version)) / 2;
    tft->drawString(version, versionX, 30);

    this->setTextSizeSmall(tft);
    auto deviceName = DeviceBase::getInstance()->getSettings()->getDeviceName();
    auto deviceNameX = (displaySettings.width - tft->textWidth(deviceName)) / 2;
    tft->drawString(deviceName, deviceNameX, displaySettings.height - 25);

    vTaskDelay(pdMS_TO_TICKS(1000 * 3));
}

void SplashScreen::buttonNextPressed()
{
}

void SplashScreen::buttonPreviousPressed()
{
}

void SplashScreen::buttonBackPressed()
{
}

void SplashScreen::buttonSelectPressed()
{
}
