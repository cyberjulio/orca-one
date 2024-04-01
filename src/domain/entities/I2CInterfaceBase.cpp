#include "I2CInterfaceBase.h"

using namespace Domain::Entities;

InterfaceType I2CInterfaceBase::getType()
{
    return InterfaceType::I2C;
}

void I2CInterfaceBase::begin()
{
	this->_wire = new TwoWire(0);
    this->_wire->begin(SDA_PIN, SCL_PIN);
}

void I2CInterfaceBase::begin(int sda_pin, int scl_pin)
{
	this->_wire = new TwoWire(0);
    this->_wire->begin(sda_pin, scl_pin);
}

void I2CInterfaceBase::loop()
{

}

void I2CInterfaceBase::end()
{
    this->_wire->end();
}
 
