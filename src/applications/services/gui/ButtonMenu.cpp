#include "ButtonMenu.h"
#include "../../../domain/entities/DeviceBase.h"

using namespace Applications::Services::GUI;
using namespace Domain::Entities;

#include <TFT_eSPI.h>

void ButtonMenu::render(std::shared_ptr<TFT_eSPI> tft)
{
    auto device = DeviceBase::getInstance();
    auto displaySettings = this->getDisplaySettings();
    auto primaryColor = colorToUInt16(device->getSettings()->getPrimaryColor());
    auto backgroundColor = colorToUInt16(device->getSettings()->getBackgroundColor());

    // Draw button border
    tft->drawRoundRect(this->_x, this->_y, displaySettings.width - 20, 25, 8, primaryColor);

    // Draw button fill
    if (this->isSelected())
        tft->fillRoundRect(this->_x, this->_y, displaySettings.width - 20, 25, 8, primaryColor);

    if (this->isSelected())
        tft->setTextColor(backgroundColor);
    else
        tft->setTextColor(primaryColor);

    this->setTextSizeSmall(tft);
    tft->setTextDatum(TL_DATUM);

    tft->drawString(this->_text, this->_x + 10, this->_y + 5);
}

void ButtonMenu::setBorderColor(int color)
{
    this->_borderColor = color;
}

void ButtonMenu::setBackgroundColor(int color)
{
    this->_backgroundColor = color;
}

void ButtonMenu::setTextColor(int color)
{
    this->_textColor = color;
}

void ButtonMenu::setSelectedTextColor(int color)
{
    this->_selectedTextColor = color;
}

void ButtonMenu::setSize(int width, int height)
{
    this->_width = width;
    this->_height = height;
}

void ButtonMenu::setPosition(int x, int y)
{
    this->_x = x;
    this->_y = y;
}

void ButtonMenu::setText(String text)
{
    this->_text = text;
}

void ButtonMenu::setSelected(bool selected)
{
    this->_selected = selected;
}

bool ButtonMenu::isSelected()
{
    return this->_selected;
}

void ButtonMenu::click()
{
    if (this->_onClick != nullptr)
        this->_onClick();
}

bool ButtonMenu::isDefinedOnClick()
{
    return this->_onClick != nullptr;
}

void ButtonMenu::setOnClick(std::function<void()> onClick)
{
    this->_onClick = onClick;
}
