#include "ScreenManager.h"
#include "../../../domain/entities/DeviceBase.h"

using namespace Applications::Services::GUI;
using namespace Domain::Entities;

ScreenManager *ScreenManager::_instance = nullptr;
bool ScreenManager::_initialized = false;

ScreenManager::ScreenManager(std::shared_ptr<TFT_eSPI> tft)
{
    if (ScreenManager::_initialized)
    {
        throw std::runtime_error("ScreenManager previous initialized. Please, define ScreenManager only time. Use: ScreenManager::getInstance()");
    }

    this->_tft = tft;
    this->_topBar = new TopBar();

    ScreenManager::_initialized = true;
    ScreenManager::_instance = this;

    auto buttonsInterface = DeviceBase::getInstance()->getInterfaces().buttonsInterface;

    auto menuScreen = this;

    if (buttonsInterface != nullptr)
    {
        buttonsInterface->registerOnClickNext([this]()
                                              { _currentScreen->buttonNextPressed(); });

        buttonsInterface->registerOnClickPrevious([this]()
                                                  { _currentScreen->buttonPreviousPressed(); });

        buttonsInterface->registerOnClickSelect([this]()
                                                { _currentScreen->buttonSelectPressed(); });

        buttonsInterface->registerOnClickBack([this]()
                                              { _currentScreen->buttonBackPressed(); });
    }
}

void ScreenManager::render(std::shared_ptr<TFT_eSPI> tft)
{
    auto device = DeviceBase::getInstance();
    auto backgroundColor = colorToUInt16(device->getSettings()->getBackgroundColor());
    tft->fillScreen(backgroundColor);
    this->setTextSizeSmall(tft);
    this->_topBar->render(tft);
    this->_currentScreen->render(tft);
}

ScreenManager *ScreenManager::getInstance()
{
    return ScreenManager::_instance;
}

void ScreenManager::render()
{
    ScreenManager::_instance->render(ScreenManager::_instance->_tft);
}

void ScreenManager::setCurrentScreen(Screen *newScreen, bool setPrevious)
{
    auto manager = ScreenManager::getInstance();
    bool isBack = manager->_currentScreen != nullptr && manager->_currentScreen->getPreviousScreen() == newScreen ? true : false;

    if (isBack)
    {
        auto screenToDelete = manager->_currentScreen;
        manager->_currentScreen = nullptr;
        delete screenToDelete;
    }
    else if (setPrevious)
    {
        newScreen->setPreviousScreen(manager->_currentScreen);
    }

    manager->_currentScreen = newScreen;

    manager->render();
}

void ScreenManager::setToPreviousScreen()
{
    if (ScreenManager::getInstance()->_currentScreen->getPreviousScreen() != nullptr)
        ScreenManager::setCurrentScreen(ScreenManager::getInstance()->_currentScreen->getPreviousScreen());
}

Screen *ScreenManager::getCurrentScreen()
{
    return ScreenManager::getInstance()->_currentScreen;
}
