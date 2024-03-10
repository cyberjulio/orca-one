#include "AboutScreen.h"
#include "../../services/gui/ScreenManager.h"
#include "../../../domain/entities/DeviceBase.h"
#include "../../Translate.h"

using namespace Applications::Settings::About;
using namespace Applications::Services::GUI;
using namespace Domain::Entities;

void AboutScreen::render(std::shared_ptr<TFT_eSPI> tft)
{
    auto device = DeviceBase::getInstance();
    auto displaySettings = this->getDisplaySettings();
    auto deviceName = device->getName();
    tft->setTextDatum(TL_DATUM);

    this->setTextSizeSmall(tft);
    auto title = String("Orca One");
    auto titleX = (displaySettings.width - tft->textWidth(title)) / 2;
    tft->drawString(title, titleX, this->_topBarHeight + 5);

    this->setTextSizeTiny(tft);
    tft->setCursor(0, this->_topBarHeight + 5 + tft->fontHeight() + 5);
    tft->println("");
    tft->println(" " + this->translate("Device") + ": " + deviceName);
    tft->println(" " + this->translate("Version") + ": " + String(BUILD_NUMBER));
    tft->println("");
    tft->println(" " + this->translate("Contributors") + ":");
    tft->println("   @cyberjulio");
    tft->println("   @marivaaldo");
    tft->println("   @n0xa");
    tft->println("");
    tft->println(" Join https://bit.ly/hackingtroop");
}

void AboutScreen::buttonSelectPressed()
{
    ScreenManager::setToPreviousScreen();
}

void AboutScreen::buttonNextPressed()
{
    ScreenManager::setToPreviousScreen();
}

void AboutScreen::buttonPreviousPressed()
{
    ScreenManager::setToPreviousScreen();
}
