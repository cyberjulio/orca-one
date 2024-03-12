#include "AbstractGuiModule.h"
#include "../../../domain/entities/DeviceBase.h"
#include "../../Translate.h"

using namespace Applications::Services::GUI;

std::shared_ptr<Domain::Entities::DisplayInterfaceBase> AbstractGuiModule::getDisplayInterface()
{
    return Domain::Entities::DeviceBase::getInstance()->getInterfaces().display;
}

DisplaySettings AbstractGuiModule::getDisplaySettings()
{
    return this->getDisplayInterface()->getSettings();
}

String AbstractGuiModule::translate(String key)
{
    return Applications::Translate::getInstance()->get(key);
}

void AbstractGuiModule::setId(String id)
{
    this->_id = id;
}

const String AbstractGuiModule::getId()
{
    return this->_id;
}

void AbstractGuiModule::setTextSizeBig(std::shared_ptr<TFT_eSPI> tft)
{
    tft->setTextSize(this->getDisplayInterface()->getTextSizeBig());
}

void AbstractGuiModule::setTextSizeMedium(std::shared_ptr<TFT_eSPI> tft)
{
    tft->setTextSize(this->getDisplayInterface()->getTextSizeMedium());
}

void AbstractGuiModule::setTextSizeSmall(std::shared_ptr<TFT_eSPI> tft)
{
    tft->setTextSize(this->getDisplayInterface()->getTextSizeSmall());
}

void AbstractGuiModule::setTextSizeTiny(std::shared_ptr<TFT_eSPI> tft)
{
    tft->setTextSize(this->getDisplayInterface()->getTextSizeTiny());
}

void AbstractGuiModule::drawBorderedText(std::shared_ptr<TFT_eSPI> tft, String text, int x, int y, int borderSize, uint16_t textColor, uint16_t borderColor)
{
    tft->setTextColor(borderColor);

    for (int i = -borderSize; i <= borderSize; i++)
    {
        for (int j = -borderSize; j <= borderSize; j++)
        {
            if (i != 0 || j != 0)
            {
                tft->setCursor(x + i, y + j);
                tft->print(text);
            }
        }
    }

    tft->setTextColor(textColor);
    tft->setCursor(x, y);
    tft->print(text);
}
