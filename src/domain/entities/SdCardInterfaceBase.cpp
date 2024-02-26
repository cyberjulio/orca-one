#include "SdCardInterfaceBase.h"

using namespace Domain::Entities;

SdCardInterfaceBase::SdCardInterfaceBase()
{
}

InterfaceType SdCardInterfaceBase::getType()
{
    return InterfaceType::SdCard;
}

void SdCardInterfaceBase::loop()
{
}

bool Domain::Entities::SdCardInterfaceBase::isActive()
{
    return this->_initialized && this->_active;
}

void SdCardInterfaceBase::begin()
{
    this->_spi = new SPIClass(SDCARD_SPI_BUS);
    this->_spi->begin(SDCARD_SCK, SDCARD_MISO, SDCARD_MOSI, SDCARD_CS);

    this->_initialized = SD.begin(SDCARD_CS, *(this->_spi));

    if (this->_initialized)
    {
        Serial.println("SDCard Initialized.");
    }
    else
    {
        Serial.println("Error while initialize SDCard!");
    }
}
