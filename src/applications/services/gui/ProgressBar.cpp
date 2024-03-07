#include "ProgressBar.h"

using namespace Applications::Services::GUI;

ProgressBar::ProgressBar()
{
    auto displaySettings = this->getDisplaySettings();
    int progressBarMargin = 10;
    this->_width = displaySettings.width - (progressBarMargin * 2);
}

void ProgressBar::render(std::shared_ptr<TFT_eSPI> tft)
{
    auto displaySettings = DeviceBase::getInstance()->getSettings();
    auto primaryColor = colorToUInt16(displaySettings->getPrimaryColor());
    auto backgroundColor = colorToUInt16(displaySettings->getBackgroundColor());
    this->setProgressColor(primaryColor);
    this->setTextColor(primaryColor);
    this->setBorderColor(primaryColor);
    this->setBackgroundColor(backgroundColor);

    tft->drawRect(this->_x, this->_y, this->_width, this->_height, this->_borderColor);
    tft->fillRect(this->_x + 1, this->_y + 1, this->_width - 2, this->_height - 2, this->_backgroundColor);

    int filledWidth = map(this->_progress, 0, 100, 0, this->_width);

    tft->fillRect(this->_x + 1, this->_y + 1, filledWidth - 2, this->_height - 2, this->_progressColor);

    this->setTextSizeSmall(tft);
    this->drawBorderedText(tft, String(this->_progress) + "%", this->_x + (this->_width / 2) - 5, this->_y + 5, 1, this->_backgroundColor, this->_progressColor);
}

void ProgressBar::setBorderColor(int color)
{
    this->_borderColor = color;
}

void ProgressBar::setBackgroundColor(int color)
{
    this->_backgroundColor = color;
}

void ProgressBar::setProgressColor(int color)
{
    this->_progressColor = color;
}

void ProgressBar::setTextColor(int color)
{
    this->_textColor = color;
}

void ProgressBar::setInvertedTextColor(int color)
{
    this->_invertedTextColor = color;
}

void ProgressBar::setWidth(int width)
{
    this->_width = width;
}

void ProgressBar::setPosition(int x, int y)
{
    this->_x = x;
    this->_y = y;
}

void ProgressBar::setProgress(int progress)
{
    if (progress < 0)
        progress = 0;
    else if (progress > 100)
        progress = 100;

    this->_progress = progress;
}

int ProgressBar::getHeight()
{
    return this->_height;
}
