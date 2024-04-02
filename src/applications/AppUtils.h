#pragma once

#include <memory>

#include "AppBase.h"

using namespace Applications;

namespace Applications
{
    class AppUtils
    {
    public:
        static void runApplication(AppBase * app);

        template <typename T>
        static void runApplication()
        {
            auto app = new T();
            AppUtils::runApplication(app);
        }
    };
}
