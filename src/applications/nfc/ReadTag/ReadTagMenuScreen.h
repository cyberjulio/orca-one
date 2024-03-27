#pragma once

#include "../../services/gui/MenuScreen.h"
#include "ReadTagRun.h"

using namespace Applications::Services::GUI;

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus
    namespace Applications::Nfc::ReadTag
    {
    class ReadTagMenuScreen : public MenuScreen
    {
      public:
        ReadTagMenuScreen(std::shared_ptr<TFT_eSPI> tft);
    };
    } // namespace Applications::Nfc::ReadTag
#ifdef __cplusplus
}
#endif // __cplusplus
