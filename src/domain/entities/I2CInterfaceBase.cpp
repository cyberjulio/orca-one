#include "I2CInterfaceBase.h"

using namespace Domain::Entities;

InterfaceType I2CInterfaceBase::getType()
{
    return InterfaceType::I2C;
}
