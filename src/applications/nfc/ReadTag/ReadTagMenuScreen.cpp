#include "ReadTagMenuScreen.h"
#include "../../services/gui/ScreenManager.h"
#include "ReadTagApp.h"

using namespace Applications::Nfc::ReadTag;
using namespace Applications::Services::GUI;

ReadTagMenuScreen::ReadTagMenuScreen(std::shared_ptr<TFT_eSPI> tft) : MenuScreen(tft)
{
    MenuItem readTag("readTag", TRANSLATE("ReadMifare"));

    readTag.setOnClick([tft]() {
        auto screnn = new ReadTagRun(tft);
        ScreenManager::setCurrentScreen(screnn);
        screnn->start();
    });

    this->addItem(readTag);
}
