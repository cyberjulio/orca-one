#pragma once

#include "../../AppBase.h"

using namespace Applications;

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus
    namespace Applications::Nfc::ReadTag
    {
    class ReadTagApp : public AppBase
    {
      public:
        void app_main(std::shared_ptr<AppContext> appContext);
    };
    } // namespace Applications::Nfc::ReadTag
#ifdef __cplusplus
}
#endif
