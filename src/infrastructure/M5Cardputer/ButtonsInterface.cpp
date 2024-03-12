#ifdef M5CARDPUTER

#include "ButtonsInterface.h"
#include "utility/Keyboard_def.h"

using namespace Infrastructure::M5Cardputer;

ButtonsInterface::ButtonsInterface() : ButtonsInterfaceBase()
{
}

void ButtonsInterface::begin()
{
}

void ButtonsInterface::loop()
{
    if (this->_keyboard == nullptr)
        this->_keyboard = DeviceBase::getInstance()->getInterfaces().keyboard;

    if (this->_keyboard->isKeyPressed(';'))
        this->_onClickPrevious.fireEvent();

    if (this->_keyboard->isKeyPressed('.'))
        this->_onClickNext.fireEvent();

    if (this->_keyboard->isKeyPressed('`'))
        this->_onClickBack.fireEvent();

    if (this->_keyboard->isKeyPressed(KEY_ENTER))
        this->_onClickSelect.fireEvent();

    this->_buttonSelect.read();

    if (this->_buttonSelect.isPressed())
        this->_onClickSelect.fireEvent();
}

#endif