#include "DeviceBase.h"

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

    if (this->_interfaces.wifiInterface == nullptr)
        this->_interfaces.wifiInterface = std::make_shared<WifiInterfaceBase>();

    if (this->_interfaces.bluetoothInterface == nullptr)
        this->_interfaces.bluetoothInterface = std::make_shared<BluetoothInterfaceBase>();

    if (this->_interfaces.sdCardInterface == nullptr)
        this->_interfaces.sdCardInterface = std::make_shared<SdCardInterfaceBase>();

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

    if (this->_interfaces.displayInterface != nullptr)
        this->_interfaces.displayInterface->begin();

    if (this->_interfaces.powerManagementInterface != nullptr)
        this->_interfaces.powerManagementInterface->begin();

    if (this->_interfaces.batteryInterface != nullptr)
        this->_interfaces.batteryInterface->begin();

    if (this->_interfaces.wifiInterface != nullptr)
        this->_interfaces.wifiInterface->begin();

    if (this->_interfaces.bluetoothInterface != nullptr)
        this->_interfaces.bluetoothInterface->begin();

    if (this->_interfaces.ledInterface != nullptr)
        this->_interfaces.ledInterface->begin();

    if (this->_interfaces.sdCardInterface != nullptr)
        this->_interfaces.sdCardInterface->begin();

    if (this->_interfaces.gpsInterface != nullptr)
        this->_interfaces.gpsInterface->begin();

    if (this->_interfaces.keyboardInterface != nullptr)
        this->_interfaces.keyboardInterface->begin();

    if (this->_interfaces.buttonsInterface != nullptr)
        this->_interfaces.buttonsInterface->begin();

    if (this->_interfaces.infraredInterface != nullptr)
        this->_interfaces.infraredInterface->begin();

    delay(100);
}

void DeviceBase::loop()
{
    if (this->_interfaces.displayInterface != nullptr)
        this->_interfaces.displayInterface->loop();

    if (this->_interfaces.powerManagementInterface != nullptr)
        this->_interfaces.powerManagementInterface->loop();

    if (this->_interfaces.batteryInterface != nullptr)
        this->_interfaces.batteryInterface->loop();

    if (this->_interfaces.wifiInterface != nullptr)
        this->_interfaces.wifiInterface->loop();

    if (this->_interfaces.bluetoothInterface != nullptr)
        this->_interfaces.bluetoothInterface->loop();

    if (this->_interfaces.ledInterface != nullptr)
        this->_interfaces.ledInterface->loop();

    if (this->_interfaces.sdCardInterface != nullptr)
        this->_interfaces.sdCardInterface->loop();

    if (this->_interfaces.gpsInterface != nullptr)
        this->_interfaces.gpsInterface->loop();

    if (this->_interfaces.keyboardInterface != nullptr)
        this->_interfaces.keyboardInterface->loop();

    if (this->_interfaces.buttonsInterface != nullptr)
        this->_interfaces.buttonsInterface->loop();

    if (this->_interfaces.infraredInterface != nullptr)
        this->_interfaces.infraredInterface->loop();

	if (this->_interfaces.i2cInterface != nullptr)
        this->_interfaces.i2cInterface->loop();

    delay(150);
}

bool DeviceBase::hasInterface(InterfaceType type)
{
    switch (type)
    {
    case InterfaceType::Display:
        return this->_interfaces.displayInterface != nullptr;
    case InterfaceType::PowerManagement:
        return this->_interfaces.powerManagementInterface != nullptr;
    case InterfaceType::Battery:
        return this->_interfaces.batteryInterface != nullptr;
    case InterfaceType::Wifi:
        return this->_interfaces.wifiInterface != nullptr;
    case InterfaceType::Bluetooth:
        return this->_interfaces.bluetoothInterface != nullptr;
    case InterfaceType::Led:
        return this->_interfaces.ledInterface != nullptr;
    case InterfaceType::SdCard:
        return this->_interfaces.sdCardInterface != nullptr;
    case InterfaceType::Gps:
        return this->_interfaces.gpsInterface != nullptr;
    case InterfaceType::Keyboard:
        return this->_interfaces.keyboardInterface != nullptr;
    case InterfaceType::Buttons:
        return this->_interfaces.buttonsInterface != nullptr;
    case InterfaceType::Infrared:
        return this->_interfaces.infraredInterface != nullptr;
    case InterfaceType::I2C:
        return this->_interfaces.i2cInterface != nullptr;
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
