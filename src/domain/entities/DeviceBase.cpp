#include "DeviceBase.h"
#include "I2CInterfaceBase.h"

using namespace Domain::Entities;

DeviceBase *DeviceBase::_instance = nullptr;
bool DeviceBase::_initialized = false;

DeviceBase::DeviceBase(Interfaces interfaces)
{
    if (DeviceBase::_initialized)
    {
        throw std::runtime_error("Device previous initialized. Please, define Device only time. Use: DeviceBase::getInstance()");
    }

    this->_interfaces = interfaces;

    if (this->_interfaces.wifi == nullptr)
        this->_interfaces.wifi = std::make_shared<WifiInterfaceBase>();

    if (this->_interfaces.bluetooth == nullptr)
        this->_interfaces.bluetooth = std::make_shared<BluetoothInterfaceBase>();

    if (this->_interfaces.sdCard == nullptr)
        this->_interfaces.sdCard = std::make_shared<SdCardInterfaceBase>();

    if (this->_interfaces.i2c == nullptr)
        this->_interfaces.i2c = std::make_shared<I2CInterfaceBase>();

    esp_chip_info(&this->_chip_info);

    DeviceBase::_initialized = true;
    DeviceBase::_instance = this;
}

DeviceBase *DeviceBase::getInstance()
{
    return DeviceBase::_instance;
}

void DeviceBase::begin()
{
    Serial.begin(115200);

    if (!SPIFFS_STORAGE.begin(true))
        Serial.println("Failed to mount SPIFFS_STORAGE");

    this->_settings = Settings::fromFile(SPIFFS_STORAGE, SETTINGS_FILE_NAME);

    if (this->_interfaces.display != nullptr)
        this->_interfaces.display->begin();

    if (this->_interfaces.powerManagement != nullptr)
        this->_interfaces.powerManagement->begin();

    if (this->_interfaces.wifi != nullptr)
        this->_interfaces.wifi->begin();

    if (this->_interfaces.bluetooth != nullptr)
        this->_interfaces.bluetooth->begin();

    if (this->_interfaces.led != nullptr)
        this->_interfaces.led->begin();

    if (this->_interfaces.sdCard != nullptr)
        this->_interfaces.sdCard->begin();

    if (this->_interfaces.gps != nullptr)
        this->_interfaces.gps->begin();

    if (this->_interfaces.keyboard != nullptr)
        this->_interfaces.keyboard->begin();

    if (this->_interfaces.buttons != nullptr)
        this->_interfaces.buttons->begin();

    if (this->_interfaces.infrared != nullptr)
        this->_interfaces.infrared->begin();

    if (this->_interfaces.microphone != nullptr)
        this->_interfaces.microphone->begin();

    if (this->_interfaces.i2c != nullptr)
        this->_interfaces.i2c->begin();

    delay(100);
}

void DeviceBase::loop()
{
    if (this->_interfaces.display != nullptr)
        this->_interfaces.display->loop();

    if (this->_interfaces.powerManagement != nullptr)
        this->_interfaces.powerManagement->loop();

    if (this->_interfaces.wifi != nullptr)
        this->_interfaces.wifi->loop();

    if (this->_interfaces.bluetooth != nullptr)
        this->_interfaces.bluetooth->loop();

    if (this->_interfaces.led != nullptr)
        this->_interfaces.led->loop();

    if (this->_interfaces.sdCard != nullptr)
        this->_interfaces.sdCard->loop();

    if (this->_interfaces.gps != nullptr)
        this->_interfaces.gps->loop();

    if (this->_interfaces.keyboard != nullptr)
        this->_interfaces.keyboard->loop();

    if (this->_interfaces.buttons != nullptr)
        this->_interfaces.buttons->loop();

    if (this->_interfaces.infrared != nullptr)
        this->_interfaces.infrared->loop();

    if (this->_interfaces.microphone != nullptr)
        this->_interfaces.microphone->loop();

	if (this->_interfaces.i2c != nullptr)
        this->_interfaces.i2c->loop();

    delay(150);
}

bool DeviceBase::hasInterface(InterfaceType type)
{
    switch (type)
    {
    case InterfaceType::Display:
        return this->_interfaces.display != nullptr;
    case InterfaceType::PowerManagement:
        return this->_interfaces.powerManagement != nullptr;
    case InterfaceType::Wifi:
        return this->_interfaces.wifi != nullptr;
    case InterfaceType::Bluetooth:
        return this->_interfaces.bluetooth != nullptr;
    case InterfaceType::Led:
        return this->_interfaces.led != nullptr;
    case InterfaceType::SdCard:
        return this->_interfaces.sdCard != nullptr;
    case InterfaceType::Gps:
        return this->_interfaces.gps != nullptr;
    case InterfaceType::Keyboard:
        return this->_interfaces.keyboard != nullptr;
    case InterfaceType::Buttons:
        return this->_interfaces.buttons != nullptr;
    case InterfaceType::Infrared:
        return this->_interfaces.infrared != nullptr;
    case InterfaceType::Microphone:
        return this->_interfaces.microphone != nullptr;
    case InterfaceType::I2C:
        return this->_interfaces.i2c != nullptr;
    default:
        return false;
    }
}

Interfaces DeviceBase::getInterfaces()
{
    return this->_interfaces;
}

esp_chip_info_t DeviceBase::getChipInfo()
{
    return this->_chip_info;
}

Settings *DeviceBase::getSettings()
{
    return this->_settings;
}

void DeviceBase::saveSettings()
{
    this->_settings->save(SPIFFS_STORAGE, SETTINGS_FILE_NAME);

    // TODO show reboot screen

    ESP.restart();
}
