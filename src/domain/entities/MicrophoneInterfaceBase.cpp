#include "MicrophoneInterfaceBase.h"

using namespace Domain::Entities;

InterfaceType MicrophoneInterfaceBase::getType()
{
    return InterfaceType::Microphone;
}
