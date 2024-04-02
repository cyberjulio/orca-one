#include "MicrophoneInterfaceBase.h"

using namespace Domain::Entities;

InterfaceType MicrophoneInterfaceBase::getType()
{
    return InterfaceType::Microphone;
}

void MicrophoneInterfaceBase::registerOnRecorded(std::function<void(RecordedSample)> handler)
{
    this->_onRecorded.addHandler(handler);
}
