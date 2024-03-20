#include "ButtonsInterfaceBase.h"

using namespace Domain::Entities;

InterfaceType ButtonsInterfaceBase::getType()
{
    return InterfaceType::Buttons;
}

void ButtonsInterfaceBase::registerOnClickPrevious(std::function<void()> handler)
{
    if (this->hasPrevious())
        this->_onClickPrevious.addHandler([handler](void *param)
                                          { handler(); });
}

void ButtonsInterfaceBase::registerOnClickSelect(std::function<void()> handler)
{
    if (this->hasSelect())
        this->_onClickSelect.addHandler([handler](void *param)
                                        { handler(); });
}

void ButtonsInterfaceBase::registerOnClickBack(std::function<void()> handler)
{
    if (this->hasBack())
        this->_onClickBack.addHandler([handler](void *param)
                                      { handler(); });
}

void ButtonsInterfaceBase::registerOnClickNext(std::function<void()> handler)
{
    if (this->hasNext())
        this->_onClickNext.addHandler([handler](void *param)
                                      { handler(); });
}
