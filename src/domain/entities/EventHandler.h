#pragma once

#include <functional>
#include <vector>

namespace Domain::Entities
{
    template <typename T>
    class GenericEventHandler
    {
    public:
        inline void addHandler(std::function<void(T)> handler)
        {
            this->_handlers.push_back(handler);
        }

        inline void fireEvent(T param)
        {
            for (const auto &handler : this->_handlers)
            {
                handler(param);
            }
        }

    protected:
        std::vector<std::function<void(T)>> _handlers = std::vector<std::function<void(T)>>();
    };

    class EventHandler : public GenericEventHandler<void *>
    {
    public:
        inline void fireEvent()
        {
            for (const auto &handler : this->_handlers)
            {
                handler(nullptr);
            }
        }
    };
}
